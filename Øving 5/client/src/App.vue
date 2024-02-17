<template>
  <div id="app">
    <code-input @compile="sendCodeToBackend"></code-input>
    <result-display :result="compilerResult"></result-display>
  </div>
</template>

<script>
import CodeInput from "@/components/CodeInput.vue";
import ResultDisplay from "@/components/ResultDisplay.vue";

export default {
  components: {
    CodeInput,
    ResultDisplay,
  },
  data() {
    return {
      compilerResult: "",
    };
  },
  methods: {
    sendCodeToBackend(code) {
      // Assuming your backend is running on port 3000
      const backendURL = "http://localhost:3000/compile";

      // Send code to backend
      fetch(backendURL, {
        method: "POST",
        headers: {
          "Content-Type": "text/plain",
        },
        body: code,
      })
        .then((response) => response.text())
        .then((result) => {
          this.compilerResult = result;
        })
        .catch((error) => {
          console.error("Error sending code to backend:", error);
        });
    },
  },
};
</script>
