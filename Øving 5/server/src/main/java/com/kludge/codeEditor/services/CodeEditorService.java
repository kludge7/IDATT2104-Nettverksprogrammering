// src/main/java/com/kludge/codeEditor/services/CodeEditorService.java
package com.kludge.codeEditor.services;

import org.springframework.stereotype.Service;

import java.io.*;

@Service
public class CodeEditorService {

    public String compileCode(String code) {
        try {
            // Create a temporary file
            File tempFile = File.createTempFile("temp", ".cpp");

            // Write the C++ code to the temporary file
            try (PrintWriter writer = new PrintWriter(tempFile)) {
                writer.write(code);
            }

            // Compile the C++ code
            Process process = Runtime.getRuntime().exec("g++ -std=c++11 " + tempFile.getPath() + " -o " + tempFile.getPath() + ".out");
            int exitCode = process.waitFor();

            // Get the compilation output
            StringBuilder compilationOutput = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    compilationOutput.append(line).append("\n");
                }
            }

            // If compilation was successful, run the compiled code
            if (exitCode == 0) {
                process = Runtime.getRuntime().exec(tempFile.getPath() + ".out");
                StringBuilder executionOutput = new StringBuilder();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        executionOutput.append(line).append("\n");
                    }
                }

                // Delete temporary files
                tempFile.delete();
                new File(tempFile.getPath() + ".out").delete();

                return executionOutput.toString();
            } else {
                // Delete temporary files
                tempFile.delete();
                new File(tempFile.getPath() + ".out").delete();

                return "Execution skipped due to compilation error";
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "Error compiling and running code";
        }
    }
}
