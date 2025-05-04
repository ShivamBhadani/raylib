#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Vertex Shader (GLSL)
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "}\n";

// Fragment Shader (GLSL)
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0, 0.4, 0.1, 1.0);\n"
    "}\n";

void setupTriangle(GLuint* VAO, GLuint* shaderProgram) {
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders into a program
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up VAO/VBO
    GLuint VBO;
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void render(GLuint VAO, GLuint shaderProgram, float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "GLFW init failed\n");
        return -1;
    }

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win1 = glfwCreateWindow(400, 300, "Triangle 1", NULL, NULL);
    GLFWwindow* win2 = glfwCreateWindow(400, 300, "Triangle 2", NULL, NULL);
    if (!win1 || !win2) {
        fprintf(stderr, "Failed to create windows\n");
        glfwTerminate();
        return -1;
    }

    GLuint vao1, prog1;
    glfwMakeContextCurrent(win1);
    glewInit();
    setupTriangle(&vao1, &prog1);

    GLuint vao2, prog2;
    glfwMakeContextCurrent(win2);
    glewInit();
    setupTriangle(&vao2, &prog2);

    while (!glfwWindowShouldClose(win1) && !glfwWindowShouldClose(win2)) {
        glfwMakeContextCurrent(win1);
        render(vao1, prog1, 0.1f, 0.1f, 0.1f); // dark bg
        glfwSwapBuffers(win1);

        glfwMakeContextCurrent(win2);
        render(vao2, prog2, 0.2f, 0.3f, 0.4f); // blueish bg
        glfwSwapBuffers(win2);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
