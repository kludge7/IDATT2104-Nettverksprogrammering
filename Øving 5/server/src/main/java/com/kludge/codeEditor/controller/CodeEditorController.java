package com.kludge.codeEditor.controller;

import java.io.IOException;

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
    public CodeEditorController(CodeEditorService codeEditorService) {
    }

    @PostMapping("/compile")
    public String compileCode(@RequestBody String code) throws IOException, InterruptedException {
        return CodeEditorService.compileAndRun(code);
    }
}
