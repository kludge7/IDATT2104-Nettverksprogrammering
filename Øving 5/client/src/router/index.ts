import { createRouter, createWebHistory } from 'vue-router'
import CodeEditorView from '../views/CodeEditorView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: CodeEditorView 
    }
  ]
})

export default router
