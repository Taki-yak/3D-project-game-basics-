#include "Engine.h"

Engine::Engine(const char* title, int width, int height) : isRunning(true) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

   
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        cleanUp();
        exit(EXIT_FAILURE);
    }

    
    glEnable(GL_DEPTH_TEST);

   
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    shaderProgram = compileShaders();
}

GLuint Engine::getShaderProgram() const {
    return shaderProgram;
}

void Engine::start(const std::function<void()>& render) {
    while (isRunning) {
        handleEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render();  
        SDL_GL_SwapWindow(window);
    }
}

void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

GLuint Engine::compileShaders() {
 
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        out vec3 ourColor;

        uniform mat4 model;       // Model transformation
        uniform mat4 view;        // Camera/view transformation
        uniform mat4 projection;  // Projection transformation

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            ourColor = aColor;
        }
    )";

 
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 ourColor;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(ourColor, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

  
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Engine::cleanUp() {
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Engine::~Engine() {
    cleanUp();
}
