#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "./src/vertexBuffer.hpp"
#include "./src/indexBuffer.hpp"

struct ShaderSource{
    std::string vertexShader;
    std::string fragmentShader;
};

static ShaderSource parseShader(const std::string& filepath){
    
    enum class shaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    while(getline(stream, line)){
        if (line.find("#shader") != std::string::npos) {
            if(line.find("Vertex") != std::string::npos){
                type = shaderType::VERTEX;
            }
            else if(line.find("Fragment") != std::string::npos){
                type = shaderType::FRAGMENT;
            }
        }else{
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int Compileshader(const std::string& source, unsigned int type){
    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    
    glShaderSource(shaderID, 1, &src, NULL);
    glCompileShader(shaderID);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout<<(type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "VERTEX")<< std::endl;
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        
        glDeleteShader(shaderID);
    }
    
    return shaderID;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vs = Compileshader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = Compileshader(fragmentShader, GL_FRAGMENT_SHADER);
    
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    
    int  success;
    char infoLog[512];
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<<"Shader Program linking error."<<std::endl;
    }
    
    glUseProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return shaderProgram;
}


int main(void)
{
    GLFWwindow* window;
    
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    glewExperimental = GL_TRUE;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if( glewInit() != GLEW_OK){
        std::cout<<"GLEW Init Failed";
    }
    
    std::cout<<glGetString(GL_VERSION);
    
    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
    };
    unsigned int indices[]={
        0,1,2,
        2,3,0
    };
    unsigned int vao;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    IndexBuffer ib(indices, 6);
    ib.Bind();
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    
    
    ShaderSource source = parseShader("shader/basic.shader");
    
    unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
    glUseProgram(shader);
    float i= 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        (i >= 1.0f) ? i= 0.0f : i = i+ 0.001f;
        
        glClearColor(0.1f,0.6f,0.4f, 1.0f);
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader, "fragColor");
        glUseProgram(shader);
        glUniform4f(vertexColorLocation, i, greenValue, 0.4f, 1.0f);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }
    
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
