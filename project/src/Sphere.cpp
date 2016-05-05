#include "Sphere.h"

namespace Crescer3D
{

void Sphere::moveForward () {
	positionz-=velocity;
}
void Sphere::moveBack(){
	positionz+=velocity;
}
void Sphere::moveLeft(){
	positionx-=velocity;
}
void Sphere::moveRight () {
	positionx+=velocity;
}
float Sphere::getRadius(){
	 return radius;
}
float Sphere::getX(){
	return positionx;
}
float Sphere::getY(){
	return positiony;
}
float Sphere::getZ(){
	return positionz;
}
vec3 Sphere::getPosition() {
	return vec3(positionx, positiony, positionz);
}
void Sphere::incrementRadius(){
	radius+=0.5;
}
void Sphere::decrementRadius(){
	radius-=0.5;
}
void Sphere::setPositionX(float x){
	positionx=x;
}
void Sphere::setPositionY(float y){
	positiony=y;
}
void Sphere::setPositionZ(float z){
	positionz=z;
}
void Sphere::setPosition(float x, float y,float z)
{
	setPositionX(x);
	setPositionY(y);
	setPositionZ(z);
}
Sphere::Sphere()
{
	positionx=0.0f;
	positiony=1.0f;
	positionz=0.0f;
	velocity = 0.5;
	radius=1.0;
}

void Sphere::init(int x, GLuint shader)
{
	id=x;
	m_Shader = shader;
	m_Model=LoadModelPlus("model/sphere/groundsphere.obj");
}


void Sphere::draw(mat4 viewMatrix, vec3 cameraPos) {
	glUseProgram(m_Shader);
	mat4 mdlViewMatrix = Mult(viewMatrix, Mult(T(positionx,positiony,positionz),S(radius,radius,radius)));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
	glUniform3fv(glGetUniformLocation(m_Shader, "cameraPosition"), 1, &cameraPos.x);
	DrawModel(m_Model, m_Shader, "inPosition", "inNormal", "inTexCoord");
}

bool Sphere::collision(Sphere* other)
{
	// Calculate the sum of the radii, then square it
	float sumradiusSquared = getRadius() + other->getRadius();
	sumradiusSquared *= sumradiusSquared;

	double deltaXSquared = getX() - other->getX(); // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = getY() - other->getY(); // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	double deltaZSquared = getZ() - other->getZ(); // calc. delta Y
	deltaZSquared *= deltaZSquared; // square delta Y
	if(deltaXSquared + deltaYSquared +deltaZSquared <= sumradiusSquared){
		return true;
	}
	return false;
}


float Sphere::SquaredDistPointAABB( float pn, float bmin, float bmax  )
{
        float out = 0;
        float v = pn;
        if ( v < bmin )
        {
            double val = (bmin - v);
            out += val * val;
        }

        if ( v > bmax )
        {
            double val = (v - bmax);
            out += val * val;
        }
        return out;
}
// True if the Sphere and AABB intersects
bool Sphere::collisionAABB(Cube* AABB)
{
	// Squared distance
    double squaredDistance = 0.0;
	vec3 BMax=AABB->getMaxBox();
	vec3 BMin=AABB->getMinBox();
    squaredDistance += SquaredDistPointAABB( positionx, BMin.x, BMax.x );
    squaredDistance += SquaredDistPointAABB( positiony, BMin.y, BMax.y );
    squaredDistance += SquaredDistPointAABB( positionz, BMin.z, BMax.z );
    // Intersection if the distance from center is larger than the radius
    // of the sphere.

    return squaredDistance <= (getRadius() *getRadius());
}

}