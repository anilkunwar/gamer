#pragma once

#include <iostream>
#include "tensor.h"

struct Vertex
{
    tensor<double,3,1> position;
    size_t marker = 0;
    bool selected = false;
    
    Vertex(): Vertex(0,0,0) {}
    Vertex(double x, double y, double z): Vertex(x,y,z, 0, false){}
    Vertex(double x, double y, double z, size_t m, bool sel){
        position[0]= x;
        position[1] = y;
        position[2] = z;
        marker = m;
        selected = sel;
    }
    Vertex(const Vertex& x) : position(x.position), marker(x.marker), selected(x.selected){}
    Vertex(const Vertex&& x) : position(std::move(x.position)), marker(std::move(x.marker)), selected(std::move(x.selected)) {}

    friend std::ostream& operator<<(std::ostream& output, const Vertex& v){
        output  << "Vertex(x:" << v[0]
                << ",y:" << v[1] 
                << ",z:" << v[2]
                << ";m:" << v.marker
                << ";sel:" << v.selected
                << ")";
        return output;
    }
    
    const double& operator[](std::size_t index) const{
        return position[index];
    }
    
    double& operator[](std::size_t index){
        return position[index];
    }
    
    void operator=(const Vertex& v){
        position = v.position;
        marker = v.marker;
        selected = v.selected;
    }
   
    bool operator==(const Vertex& rhs) const{
        Vertex temp(rhs); 
        if(position != temp.position) return false;
        if(marker != temp.marker) return false;
        if(selected != temp.selected) return false;
        return true;
    }

    bool operator!=(const Vertex& rhs) const{
        return !(*this == rhs);
    }

    Vertex& operator+=(const Vertex& rhs){
        // retains the marker of the lhs 
        position += rhs.position;
        selected = selected || rhs.selected; 
        return *this;
    }
    
    Vertex& operator-=(const Vertex& rhs){
        //retains the marker of the lhs
        position -= rhs.position;
        selected = selected || rhs.selected;
        return *this;
    }
    
    Vertex& operator*=(double x){
        position *= x;
        return *this;
    }

    Vertex& operator/=(double x){
        position /=x;
        return *this;
    }
};

Vertex operator+(const Vertex& A, const Vertex& B);
Vertex operator-(const Vertex& A, const Vertex& B);
Vertex operator*(double x, const Vertex& A);
Vertex operator/(const Vertex& A, double x);
