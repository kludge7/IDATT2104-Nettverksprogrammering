package com.kludge.codeEditor.model;

public class CodeEditorModel {
    private String compilationOutput;
    private String executionOutput;

    public CodeEditorModel() {
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
