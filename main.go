package main

import (
	"bytes"
	_ "embed"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"text/template"
)

type MethodData struct {
	Type       string
	Name       string
	Parameters string
	Const      bool
}

type InterfaceData struct {
	Includes  []string
	Namespace string
	Interface string
	Methods   []MethodData
}

type TemplateData struct {
	Includes   []string
	Interfaces []InterfaceData
}

//go:embed template.templ
var templateFile string

func main() {
	targetDir := os.Args[1]
	err := filepath.Walk(targetDir, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if !info.IsDir() && (filepath.Ext(path) == ".h" || filepath.Ext(path) == ".hpp") {
			err := processFile(path, targetDir)
			if err != nil {
				fmt.Println("Error processing file:", err)
			}
		}
		return nil
	})
	if err != nil {
		fmt.Println("Error walking the path:", err)
		return
	}
	fmt.Println("Mock classes generated successfully.")
}

func processFile(targetFile, baseDir string) error {
	println("Processing file:", targetFile)
	content, err := os.ReadFile(targetFile)
	if err != nil {
		return fmt.Errorf("error reading target file: %w", err)
	}
	interfaceData := parseInterfaceData(string(content))
	if len(interfaceData) == 0 {
		println("No interfaces found in file.")
		return nil
	}
	relativePath, err := filepath.Rel(baseDir, targetFile)
	if err != nil {
		return fmt.Errorf("error getting relative path: %w", err)
	}
	templateData := TemplateData{
		Includes:   []string{relativePath, "gmock/gmock.h"},
		Interfaces: interfaceData,
	}
	outputPath := filepath.Join(filepath.Dir(targetFile), strings.TrimSuffix(filepath.Base(targetFile), filepath.Ext(targetFile))+"Mocks.h")
	return generateFile(templateData, outputPath)
}

func generateFile(data TemplateData, path string) error {
	tmpl, err := template.New("mock").Parse(templateFile)
	if err != nil {
		return fmt.Errorf("error parsing template: %w", err)
	}
	var output bytes.Buffer
	err = tmpl.Execute(&output, data)
	if err != nil {
		return fmt.Errorf("error executing template: %w", err)
	}
	err = os.WriteFile(path, output.Bytes(), 0644)
	if err != nil {
		return fmt.Errorf("error writing output file: %w", err)
	}
	return nil
}
