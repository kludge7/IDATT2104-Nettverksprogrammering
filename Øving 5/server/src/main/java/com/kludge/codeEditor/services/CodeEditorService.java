package com.kludge.codeEditor.services;

import org.springframework.stereotype.Service;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

@Service
public class CodeEditorService {
    public static String compileAndRun(String sourceCode) throws IOException, InterruptedException {
        File tempFile = File.createTempFile("temp", ".cpp");
        try (PrintWriter writer = new PrintWriter(new FileWriter(tempFile))) {
            writer.write(sourceCode);
        }

        ProcessBuilder processBuilder = new ProcessBuilder(
                "docker", "run", "-v", tempFile.getParent() + ":/code", "gcc:latest", "sh", "-c",
                "g++ /code/" + tempFile.getName() + " -o /code/a.out && /code/a.out");
        processBuilder.redirectErrorStream(true);

        Process process = processBuilder.start();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor(); 
            return output.toString();
        } finally {
            tempFile.delete();
        }
    }
}