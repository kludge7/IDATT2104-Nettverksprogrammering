<template>
    <div>
      <h2>Compilation Result:</h2>
      <pre>{{ result }}</pre>
    </div>
  </template>
  
  <script>
  export default {
    props: {
      result: String,
    },
  };
  </script>
  