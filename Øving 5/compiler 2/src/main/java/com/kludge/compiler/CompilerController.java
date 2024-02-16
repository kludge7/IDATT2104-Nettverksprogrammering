package com.kludge.compiler;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

@RestController
public class CompilerController {

    @PostMapping("/compile")
    public String compileCode(@RequestBody String code) {
        try {
            // Create a temporary file
            File tempFile = File.createTempFile("temp", ".java");
            
            // Write code to the temporary file
            try (FileWriter writer = new FileWriter(tempFile)) {
                writer.write(code);
            }

            // Compile and run the code
            Process process = Runtime.getRuntime().exec("javac " + tempFile.getAbsolutePath());
            process.waitFor();
            process = Runtime.getRuntime().exec("java -cp " + tempFile.getParent() + " " + tempFile.getName());

            // Capture the output
            String output = IOUtils.toString(process.getInputStream(), Charset.defaultCharset());

            // Delete the temporary file
            tempFile.delete();

            return output;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "Error occurred: " + e.getMessage();
        }
    }
}
