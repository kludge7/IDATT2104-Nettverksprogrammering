package com.kludge.codeEditor.controller;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import com.kludge.codeEditor.services.CodeEditorService;

@RestController
@RequestMapping("/codeEditor")
@CrossOrigin(origins = "http://localhost:5173")
public class CodeEditorController {
    private final CodeEditorService codeEditorService;

    public CodeEditorController(CodeEditorService codeEditorService) {
        this.codeEditorService = codeEditorService;
    }

    @PostMapping("/compile")
    public String compileCode(@RequestBody String code) {
        return codeEditorService.compileCode(code);
    }
}
