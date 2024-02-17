// src/main/java/com/kludge/codeEditor/model/CodeEditorModel.java
package com.kludge.codeEditor.model;

public class CodeEditorModel {
    private String compilationOutput;
    private String executionOutput;

    // Constructors, getters, and setters

    public CodeEditorModel() {
        // Default constructor
    }

    public CodeEditorModel(String compilationOutput, String executionOutput) {
        this.compilationOutput = compilationOutput;
        this.executionOutput = executionOutput;
    }

    public String getCompilationOutput() {
        return compilationOutput;
    }

    public void setCompilationOutput(String compilationOutput) {
        this.compilationOutput = compilationOutput;
    }

    public String getExecutionOutput() {
        return executionOutput;
    }

    public void setExecutionOutput(String executionOutput) {
        this.executionOutput = executionOutput;
    }
}
