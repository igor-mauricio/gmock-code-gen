package main

import (
	"bytes"
	_ "embed"
	"fmt"
	"os"
	"text/template"
)

type MethodData struct {
	Type       string
	Name       string
	Parameters string
	Const      bool
}

type InterfaceData struct {
	Namespace string
	Includes  []string
	Interface string
	Methods   []MethodData
}

//go:embed template.templ
var templateFile string

func main() {
	targetFile := os.Args[1]
	content, err := os.ReadFile(targetFile)
	if err != nil {
		fmt.Println("Error reading target file:", err)
		return
	}
	interfaceData := parseInterfaceData(string(content))
	tmpl, err := template.New("mock").Parse(templateFile)
	if err != nil {
		fmt.Println("Error parsing template:", err)
		return
	}
	var output bytes.Buffer
	err = tmpl.Execute(&output, interfaceData)
	if err != nil {
		fmt.Println("Error executing template:", err)
		return
	}
	outputFile := "./output.h"
	err = os.WriteFile(outputFile, output.Bytes(), 0644)
	if err != nil {
		fmt.Println("Error writing output file:", err)
		return
	}
	fmt.Println("Mock class generated successfully.")
}
