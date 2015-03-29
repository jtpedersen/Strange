#include <SDL2/SDL.h>

#include "StrangeAttractor.h"
#include "StrangeSearcher.h"
#include "StrangeGenerator.h"
#include "Rater.h"



#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>// glm::vec3
#include <glm/vec4.hpp>// glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> //lookAt etc
#include <glm/gtx/transform.hpp>
#include <glm/gtx/color_space.hpp>
#include <glm/ext.hpp> // << friends

#include <vector>
#include <memory>
#include <iostream>
using namespace std;
using namespace glm;


const int WIDTH  = 888;
const int HEIGHT = 888;

SDL_Renderer *renderer = nullptr;
SDL_Window   *win      = nullptr;

vec3 rotations(0,0,0);
float cam_scale = 130.0f;

auto ss = StrangeSearcher();
auto strangeGenerator = StrangeGenerator();

void nextAttractor() {
    ss.find(1337);
    strangeGenerator.setSA(ss.getSA());
}

mat4 mvp() {
    auto model = mat4(1.0);

    vec3 center = ss.getAABB().center();
    
    model = model * rotate(rotations[0], vec3(1.0f, 0.0f, 0.0f));
    model = model * rotate(rotations[1], vec3(0.0f, 1.0f, 0.0f));
    model = model * rotate(rotations[2], vec3(0.0f, 0.0f, 1.0f));

    model = translate(model, -center);

    auto view = lookAt(vec3(0,0,1), vec3(0.0), vec3(0,1,0));

    auto projection = translate(mat4(1.0), vec3(WIDTH/2, HEIGHT/2, 0));
    projection = scale(projection, vec3(cam_scale));

    return  projection * view * model;
}

vector<SDL_Point> glm2sdl(const vector<vec3>& pts) {
    auto sdlpts = vector<SDL_Point>();
    const auto cam = mvp();
    for(const auto p : pts) {
	auto pixel = cam * vec4(p, 1.0);
	auto x = static_cast<int>(pixel.x);
	auto y = static_cast<int>(pixel.y);
//	cout << to_string(p) <<  "-> (" << x << ", " << y << ")" << to_string(pixel) << endl;
	sdlpts.emplace_back( SDL_Point{x,y});
    }
    return sdlpts;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    try {
	strangeGenerator.startPoint(1000);
	strangeGenerator.warmup();
    } catch (const std::runtime_error& e) {
	nextAttractor();
	return;
    }

    auto sdlpts = glm2sdl(strangeGenerator.generate(100000));
    if (SDL_RenderDrawPoints(renderer, sdlpts.data(), sdlpts.size())) 
	printf("SDL_RenderDrawPoints failed: %s\n", SDL_GetError());
}

void init() {
    auto rater = std::make_shared<VolumeRater>(.1);
    ss.setRater(rater);
    nextAttractor();
}

int main(int argc, char **argv) {

    if (0 != SDL_Init(SDL_INIT_EVERYTHING) ) exit(42);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL, &win, &renderer);
    if(nullptr == win || nullptr == renderer) exit(42);
    
    SDL_Event e;
    float fps = 10.0;
    auto start_time = SDL_GetTicks();

    init();
    
    while(1) {

// calc FPS
	auto end_time = SDL_GetTicks();
	auto dt = end_time - start_time;
// limit FPS
	while (dt < 10) {
	    SDL_Delay(10);
	    end_time = SDL_GetTicks();
	    dt = end_time - start_time;
	}
	fps = fps * .9 + .1 * (1000.0 / dt);
	start_time = end_time;

	render();

// check input
	while (SDL_PollEvent(&e)){
	    if (e.type == SDL_QUIT || SDLK_q == e.key.keysym.sym) exit(0);
	    if (SDLK_UP   == e.key.keysym.sym) cam_scale *= 1.05;
	    if (SDLK_DOWN == e.key.keysym.sym) cam_scale *= 0.95;
	    if (SDLK_w == e.key.keysym.sym) rotations[1] += .1;
	    if (SDLK_a == e.key.keysym.sym) rotations[1] -= .1;
	    if (SDLK_s == e.key.keysym.sym) rotations[0] += .1;
	    if (SDLK_d == e.key.keysym.sym) rotations[0] -= .1;
	    if (SDLK_r == e.key.keysym.sym) rotations[2] += .1;
	    if (SDLK_e == e.key.keysym.sym) rotations[2] -= .1;
	    if (SDLK_n == e.key.keysym.sym) nextAttractor();


	}

// display
	char buf[512];
	sprintf(buf, "%s (%3d ms, %.2f fps)",
		argv[0], dt, fps);
	SDL_SetWindowTitle(win, buf);
	SDL_RenderPresent(renderer);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

