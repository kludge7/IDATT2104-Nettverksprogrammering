package com.kludge.codeEditor.model;

public class CodeEditorModel {
    private String executionOutput;

    public CodeEditorModel() {
    }

    public CodeEditorModel(String executionOutput) {
        this.executionOutput = executionOutput;
    }

    public String getExecutionOutput() {
        return executionOutput;
    }

    public void setExecutionOutput(String executionOutput) {
        this.executionOutput = executionOutput;
    }
}
