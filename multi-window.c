#include <GLFW/glfw3.h>
#include <stdio.h>

void RenderColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

typedef struct{
    float x;
    float y;
}vec2;

int main(void) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    vec2 dim = {2000,1600};

    GLFWwindow* win1 = glfwCreateWindow(dim.x,dim.y, "Window 1", NULL, NULL);
    GLFWwindow* win2 = glfwCreateWindow(dim.x,dim.y, "Window 2", NULL, NULL);

    if (!win1 || !win2) {
        fprintf(stderr, "Failed to create one or both windows\n");
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(win1) && !glfwWindowShouldClose(win2)) {
        // Render in window 1
        glfwMakeContextCurrent(win1);
        RenderColor(0.7f, 0.7f, 0.7f); // Light gray
        glfwSwapBuffers(win1);

        glfwMakeContextCurrent(win2);
        RenderColor(0.2f, 0.4f, 0.8f); // Blue
        glfwSwapBuffers(win2);

        glfwPollEvents();
    }

    glfwDestroyWindow(win1);
    glfwDestroyWindow(win2);
    glfwTerminate();
    return 0;
}