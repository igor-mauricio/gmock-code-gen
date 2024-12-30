package main

import (
	"bytes"
	_ "embed"
	"fmt"
	"os"
	"regexp"
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
	Namespace string
	Includes  []string
	Interface string
	Methods   []MethodData
}

//go:embed template.templ
var templateFile string

func main() {
	// Read the target file
	targetFile := os.Args[1]
	content, err := os.ReadFile(targetFile)
	if err != nil {
		fmt.Println("Error reading target file:", err)
		return
	}

	// Parse the interface data
	interfaceData := parseInterfaceData(string(content))

	// Generate the mock class
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

	// Write the output to a file
	outputFile := "./output.h"
	err = os.WriteFile(outputFile, output.Bytes(), 0644)
	if err != nil {
		fmt.Println("Error writing output file:", err)
		return
	}

	fmt.Println("Mock class generated successfully.")
}

func parseInterfaceData(content string) InterfaceData {
	// Remove comments and clean up the interface string
	commentStarRgx := regexp.MustCompile(`/\*[\s\S]*?\*/`)
	commentBackSpaceRgx := regexp.MustCompile(`//.*`)
	voidFuncRgx := regexp.MustCompile(`\(\s*void\s*\)`)
	dtor := regexp.MustCompile(`\s*virtual\s+~\w+\s*\(\s*\)\s*(?:;\s*|\{\s*\})`)

	cleanedContent := commentStarRgx.ReplaceAllString(content, "")
	cleanedContent = commentBackSpaceRgx.ReplaceAllString(cleanedContent, "")
	cleanedContent = voidFuncRgx.ReplaceAllString(cleanedContent, "( )")
	cleanedContent = dtor.ReplaceAllString(cleanedContent, "")

	// Extract namespace, class, and methods
	namespaceRe := regexp.MustCompile(`namespace\s+(\w+)\s*{`)
	namespaceMatch := namespaceRe.FindStringSubmatch(cleanedContent)
	namespace := ""
	if len(namespaceMatch) > 0 {
		namespace = namespaceMatch[1]
	}

	singleLine := strings.ReplaceAll(cleanedContent, "\n", "")
	classRe := regexp.MustCompile(`class\s+(\w+)\s*.*?{\s*.*?public:\s*(.*?)\s*};`)
	classMatch := classRe.FindStringSubmatch(singleLine)

	if len(classMatch) == 0 {
		fmt.Println("No class definition found")
		return InterfaceData{}
	}

	interfaceName := classMatch[1]
	methodsStr := classMatch[2]

	methodsRe := regexp.MustCompile(`virtual\s+(.*?)\s+(\w+)\s*\(\s*(.*?)\s*\)\s*(\w*)\s*=\s*0\s*;`)
	methodMatches := methodsRe.FindAllStringSubmatch(methodsStr, -1)

	var methods []MethodData
	for _, match := range methodMatches {
		methods = append(methods, MethodData{
			Type:       match[1],
			Name:       match[2],
			Parameters: "(" + match[3] + ")",
			Const:      match[4] == "const",
		})
	}

	return InterfaceData{
		Namespace: namespace,
		Includes:  []string{"target.h", "gmock/gmock.h"},
		Interface: interfaceName,
		Methods:   methods,
	}
}
