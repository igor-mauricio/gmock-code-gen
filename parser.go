package main

import (
	"fmt"
	"regexp"
	"strings"
)

func cleanContent(content string) string {
	multilineCommentRe := regexp.MustCompile(`/\*[\s\S]*?\*/`)
	singleLineCommentRe := regexp.MustCompile(`//.*`)
	voidFuncRe := regexp.MustCompile(`\(\s*void\s*\)`)
	destructorRe := regexp.MustCompile(`\s*virtual\s+~\w+\s*\(\s*\)\s[^;]*;`)
	cleanedContent := multilineCommentRe.ReplaceAllString(content, "")
	cleanedContent = singleLineCommentRe.ReplaceAllString(cleanedContent, "")
	cleanedContent = voidFuncRe.ReplaceAllString(cleanedContent, "( )")
	cleanedContent = destructorRe.ReplaceAllString(cleanedContent, "")
	return cleanedContent
}

func parseNamespace(content string) string {
	namespaceRe := regexp.MustCompile(`namespace\s+(\w+)\s*{`)
	namespaceMatch := namespaceRe.FindStringSubmatch(content)
	namespace := ""
	if len(namespaceMatch) > 0 {
		namespace = namespaceMatch[1]
	}
	return namespace
}

func parseInterfaceData(content string) []InterfaceData {
	cleanedContent := cleanContent(content)
	namespace := parseNamespace(cleanedContent)
	singleLine := strings.ReplaceAll(cleanedContent, "\n", "")
	classRe := regexp.MustCompile(`class\s+(\w+)\s*.*?{\s*.*?public:\s*(.*?)\s*};`)
	classesMatch := classRe.FindAllStringSubmatch(singleLine, -1)
	if len(classesMatch) == 0 {
		fmt.Println("No class definition found")
		return []InterfaceData{}
	}

	var interfacesData []InterfaceData

	for _, classMatch := range classesMatch {
		interfaceName := classMatch[1]
		methodsStr := classMatch[2]
		methodsRe := regexp.MustCompile(`virtual\s+(.*?)\s+(\w+)\s*\(\s*(.*?)\s*\)\s*(\w*)\s*=\s*0\s*;`)
		methodMatches := methodsRe.FindAllStringSubmatch(methodsStr, -1)
		if len(methodMatches) == 0 {
			fmt.Println("No pure virtual functions found at class", interfaceName)
			continue
		}
		var methods []MethodData
		for _, match := range methodMatches {
			methods = append(methods, MethodData{
				Type:       match[1],
				Name:       match[2],
				Parameters: "(" + match[3] + ")",
				Const:      match[4] == "const",
			})
		}
		interfacesData = append(interfacesData, InterfaceData{
			Namespace: namespace,
			Includes:  []string{"target.h", "gmock/gmock.h"},
			Interface: interfaceName,
			Methods:   methods,
		})

	}
	return interfacesData
}
