package com.kludge.compiler;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

import org.springframework.stereotype.Service;

@Service
public class CompilerService {

    public String compileAndRunCode(String code) {
        try {
            // Write code to a temporary file
            Path tempFile = Files.createTempFile("temp", ".cpp");
            Files.write(tempFile, code.getBytes(), StandardOpenOption.WRITE);

            // Compile and run code
            Process process = new ProcessBuilder("g++", tempFile.toString(), "-o", tempFile.toString().replace(".cpp", ""))
                    .start();
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                Process runProcess = new ProcessBuilder(tempFile.toString().replace(".cpp", "")).start();
                return readProcessOutput(runProcess);
            } else {
                return "Compilation Error";
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "Error occurred";
        }
    }

    private String readProcessOutput(Process process) throws IOException {
        byte[] outputBytes = process.getInputStream().readAllBytes();
        return new String(outputBytes);
    }
}
