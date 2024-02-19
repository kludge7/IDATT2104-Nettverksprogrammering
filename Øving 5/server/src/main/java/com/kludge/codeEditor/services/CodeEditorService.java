package com.kludge.codeEditor.services;

import org.springframework.stereotype.Service;

import java.io.*;

@Service
public class CodeEditorService {

    @SuppressWarnings("deprecation")
    public String compileCode(String code) {
        try {
            File tempFile = File.createTempFile("temp", ".cpp");

            try (PrintWriter writer = new PrintWriter(tempFile)) {
                writer.write(code);
            }

            Process process = Runtime.getRuntime().exec("g++ -std=c++11 " + tempFile.getPath() + " -o " + tempFile.getPath() + ".out");
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                process = Runtime.getRuntime().exec(tempFile.getPath() + ".out");
                StringBuilder executionOutput = new StringBuilder();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        executionOutput.append(line).append("\n");
                    }
                }

                tempFile.delete();
                new File(tempFile.getPath() + ".out").delete();

                return executionOutput.toString();
            } else {
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
