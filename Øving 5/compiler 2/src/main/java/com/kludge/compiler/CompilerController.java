package com.kludge.compiler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/compiler")
public class CompilerController {

    @Autowired
    private CompilerService compilerService;

    @PostMapping("/compile")
    public String compileAndRunCode(@RequestBody String code) {
        return compilerService.compileAndRunCode(code);
    }
}
