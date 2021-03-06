#include "Line2D.hpp"
void Line2D::setPoint1(Vector2D<double> t_point){
    point1=t_point;
    diff=point2-point1;
}
void Line2D::setPoint2(Vector2D<double> t_point){
    point2=t_point;
    diff=point2-point1;
}
Vector2D<double> Line2D::getPoint1(){
    return point1;
}
Vector2D<double> Line2D::getPoint2(){
    return point2;
}
Line2D::Line2D(){
    point1.x=0;
    point1.y=0;
    point2.x=1;
    point2.y=0;
    diff=point2-point1;
}
double Line2D::getLength(){
    return Vector2D<double>::getL2Norm(diff);
}
double Line2D::getAngle(){
    return Vector2D<double>::getDirection(diff);
}
Vector2D<double> Line2D::getCenter(){
    Vector2D<double> t_results;
    t_results.x=(point1.x+point2.x)/2.;
    t_results.y=(point1.y+point2.y)/2.;
    return t_results;
}

void Line2D::scaleBy(double t_scale){
    Line2D t_aux_line=*this;
    t_aux_line.translateBy(this->getPoint1()*-1.);
    t_aux_line.setPoint2(t_aux_line.getPoint2()*t_scale);
    t_aux_line.translateBy(this->getPoint1());
    this->setPoint1(t_aux_line.getPoint1());
    this->setPoint2(t_aux_line.getPoint2());
}
void Line2D::translateBy(Vector2D<double> t_offset){
    setPoint1(point1+t_offset);
    setPoint2(point2+t_offset);
}


// This is used to write Line2D::getClosestPoint. Source: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
// float minimum_distance(vec2 v, vec2 w, vec2 p) {
//   // Return minimum distance between line segment vw and point p
//   const float l2 = length_squared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
//   if (l2 == 0.0) return distance(p, v);   // v == w case
//   // Consider the line extending the segment, parameterized as v + t (w - v).
//   // We find projection of point p onto the line. 
//   // It falls where t = [(p-v) . (w-v)] / |w-v|^2
//   // We clamp t from [0,1] to handle points outside the segment vw.
//   const float t = max(0, min(1, dot(p - v, w - v) / l2));
//   const vec2 projection = v + t * (w - v);  // Projection falls on the segment
//   return distance(p, projection);
// }
Vector2D<double> Line2D::getClosestPoint(Vector2D<double> t_point){
    Vector2D<double> t_res;
    double t_aux1=Vector2D<double>::getL2NormSquared(diff);
    if (t_aux1==0.0){
        return this->getPoint1();
    }
    double t=std::max<double>(0.,std::min<double>(1,Vector2D<double>::dotProduct(t_point-this->getPoint1(),this->getPoint2()-this->getPoint1())/t_aux1));
    t_res=this->getPoint1()+(this->getPoint2() - this->getPoint1())*t;
    return t_res;
}


bool Line2D::checkPointIntesection(Vector2D<double> t_point){
    Vector2D<double> closest_pt=getClosestPoint(t_point);
    if (Vector2D<double>::getL2NormSquared(closest_pt-t_point)<min_sqr_dist_for_intersection){
        return true;
    }
    return false;
}