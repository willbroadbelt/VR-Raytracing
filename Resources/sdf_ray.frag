#version 330

uniform vec2 resolution;
uniform float currentTime;
uniform vec3 camPos;
uniform vec3 camDir;
uniform vec3 camUp;
uniform sampler2D tex;
uniform bool showStepDepth;

in vec3 pos;

out vec3 color;

#define PI 3.1415926535897932384626433832795
#define RENDER_DEPTH 100
#define CLOSE_ENOUGH 0.00001

#define BACKGROUND -1
#define BALL 0
#define BASE 1

#define GRADIENT(pt, func) vec3( \
    func(vec3(pt.x + 0.0001, pt.y, pt.z)) - func(vec3(pt.x - 0.0001, pt.y, pt.z)), \
    func(vec3(pt.x, pt.y + 0.0001, pt.z)) - func(vec3(pt.x, pt.y - 0.0001, pt.z)), \
    func(vec3(pt.x, pt.y, pt.z + 0.0001)) - func(vec3(pt.x, pt.y, pt.z - 0.0001)))

const vec3 LIGHT_POS[] = vec3[](vec3(5, 18, 10));

///////////////////////////////////////////////////////////////////////////////

vec3 getBackground(vec3 dir) {
  float u = 0.5 + atan(dir.z, -dir.x) / (2 * PI);
  float v = 0.5 - asin(dir.y) / PI;
  vec4 texColor = texture(tex, vec2(u, v));
  return texColor.rgb;
}

vec3 getRayDir() {
  vec3 xAxis = normalize(cross(camDir, camUp));
  return normalize(pos.x * (resolution.x / resolution.y) * xAxis + pos.y * camUp + 5 * camDir);
}

///////////////////////////////////////////////////////////////////////////////

float sphere(vec3 pt) {
  return length(pt) - 1;
}

float cube(vec3 pt) {
	vec3 d = abs(pt) - vec3(1); //radius of 1
	return min(max(d.x, max(d.y,d.z)), 0.0) + length(max(d, 0.0));
}

float torus(vec3 pt, vec2 rs){
	vec2 q = vec2(length(pt.xz)-rs.x,pt.y);
	return length(q) - rs.y;
}

float sdPlane(vec3 pt, vec4 n){
	//vec4 norm = normalize(n);
	return dot(pt,n.xyz) +n.w;
}

float tCube(vec3 pt, vec3 pos){
	return cube(pt - pos);
}
float tSphere(vec3 pt, vec3 pos){
	return sphere(pt - pos);
}


float smin(float a, float b) {//Blend
	float k = 0.2;
	float h = clamp(0.5 + 0.5 * (b-a) /k, 0, 1);
	return mix(b, a, h) - k * h * (1-h);
}

float CubesAndSpheres(vec3 pt) {
  float fScene = 0;
  
  float aC = tCube(pt, vec3(-3,0,-3));
  float aS = tSphere(pt, vec3(-2,0,-2));
  float un = min(aC,aS);//union
  fScene = un;
  
  float bC = tCube(pt, vec3(3,0,-3));
  float bS = tSphere(pt, vec3(4,0,-2));
  float difference = max(bC,-bS);
  fScene = min(fScene,difference);
  
  float cC = tCube(pt, vec3(-3,0,3));
  float cS = tSphere(pt, vec3(-2,0,4));
  float blend = smin(cC,cS);
  fScene = min(fScene,blend);
  
  float dC = tCube(pt, vec3(3,0,3));
  float dS = tSphere(pt, vec3(4,0,4));
  float intersection = max(dC,dS);
  fScene = min(fScene,intersection);
  
  return fScene;
}

float TorusScene(vec3 pt){
	float fScene = torus(pt - vec3(0,3,0), vec2(3,1));
	
	return fScene;
}

float sceneWithPlane(vec3 pt,float scene){
	float plane = sdPlane(pt-vec3(0,-1,0), vec4(0,1,0,1));
  	return min(scene, plane);
}


vec3 getNormal(vec3 pt) {
  return normalize(GRADIENT(pt, sphere));
}

vec3 getColor(vec3 pt) {
if(pt.y<-1){
	float objs = CubesAndSpheres(pt);
	float split = mod(objs,1);
	float border = mod(objs,5);
	if(4.75<=border){
		return vec3(0);
	}else{
		return mix(vec3(0.4,1,0.4),vec3(0.4,0.4,1), split);
	}
}else{
  return vec3(1);
}

}

///////////////////////////////////////////////////////////////////////////////

float shade(vec3 eye, vec3 pt, vec3 n) {
  float val = 0;
  float ambCo = 0.4;//Supposed to be 0.1 but is quite dark.
  float diffCo = 1;
  float specCo  = 1;
  float specShin = 256;
  
  vec3 e = normalize(pt-eye);
  
  val += ambCo;  // Ambient
  
  
  for (int i = 0; i < LIGHT_POS.length(); i++) {
    vec3 l = normalize(LIGHT_POS[i] - pt); 
    float nDotL = clamp(0,dot(n, l), 1);
    vec3 r = (reflect(l,n));
    
    val += diffCo * nDotL;
    val += specCo * pow(clamp(0, dot(e,r), 1),specShin);
  }
  return val;
}

vec3 illuminate(vec3 camPos, vec3 rayDir, vec3 pt) {
  vec3 c, n;
  n = getNormal(pt);
  c = getColor(pt);
  return shade(camPos, pt, n) * c;
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

vec3 raymarch(vec3 camPos, vec3 rayDir) {
  int step = 0;
  float t = 0;
  
  

  for (float d = 1000; step < RENDER_DEPTH && abs(d) > CLOSE_ENOUGH; t += abs(d)) {
   // d = cube(camPos + t * rayDir);
   d = sceneWithPlane(camPos + t * rayDir,CubesAndSpheres(camPos + t * rayDir));
   //d = sceneWithPlane(camPos + t * rayDir,TorusScene(camPos + t * rayDir));
    step++;
  }

  if (step == RENDER_DEPTH) {
    return getBackground(rayDir);
  } else if (showStepDepth) {
    return vec3(float(step) / RENDER_DEPTH);
  } else {
    return illuminate(camPos, rayDir, camPos + t * rayDir);
  }
}

///////////////////////////////////////////////////////////////////////////////

void main() {
  color = raymarch(camPos, getRayDir());
}