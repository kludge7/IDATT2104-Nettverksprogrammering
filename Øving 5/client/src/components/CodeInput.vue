<template>
    <div>
      <textarea v-model="code" rows="10" cols="50"></textarea>
      <button @click="compileCode">Compile</button>
    </div>
  </template>
  
  <script>
  export default {
    data() {
      return {
        code: "",
      };
    },
    methods: {
      compileCode() {
        this.$emit("compile", this.code);
      },
    },
  };
  </script>
  