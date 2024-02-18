<template>
    <div class="code-editor">
        <textarea v-model="code" placeholder="Enter C++ code"></textarea>
        <button @click="compileCode">Compile Code</button>
        <div v-if="output" class="output-section">
        <h3>Compilation Output:</h3>
        <pre>{{ output }}</pre>
    </div>
    </div>
</template>
<script setup lang="ts">
    import { ref } from 'vue';
    const code = ref('');
    const output = ref('');
    
    const compileCode = async () => {
    try {
        const response = await fetch('http://localhost:8080/codeEditor/compile', {
            method: 'POST',
            headers: {
                'Content-Type': 'text/plain',
            },
            body: code.value,
        });
        const data = await response.text();
        output.value = data;
    } catch (error) {
        console.error('Error compiling code:', error);
        output.value = 'Error compiling code.';
    }
};
</script>
<style scoped>
.code-editor {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;  
    min-width: 600px;
    margin: 0 auto;
    padding: 20px;
    height: 100vh; 
}


textarea {
    width: 100%;
    height: 200px;
}

button {
    width: 100%;
    padding: 10px;
    background-color: #4caf50;
    color: #fff;
    border: none;
    cursor: pointer;
}

button:hover {
    background-color: #45a049;
}

.output-section {
    margin-top: 20px;
    border: 1px solid #ddd;
    padding: 10px;
    background-color: #f9f9f9;
    color: #000000;
}

pre {
    white-space: pre-wrap;
}
</style>