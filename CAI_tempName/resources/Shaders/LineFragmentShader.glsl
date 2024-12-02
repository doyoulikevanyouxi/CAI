#version 330 core
in vec2 center;
in vec2 size;
in vec4 color;
in vec2 startPoint;
in vec2 endPoint;
in float line_thickness;
//使用该着色器我们需要一个几何着色器，因为传入的顶点是两个顶点，我们需要将其变成矩形,利用几何着色器增加顶点输出

//分辨率
uniform vec2 iResolution;
out vec4 fragColor;

//a表示该函数的x坐标，b表示y坐标，thickness表示线的宽度，edge_thickness表示平滑区间
//该函数的a,b其实并不是坐标，而是告诉在a的哪些范围内的b可以绘制，所以线的定义在函数外定义
//同时需要注意坐标是属于哪个坐标
float lineSDF(float y,float y2,float thickness){
   float half_thickness = thickness*0.5;
   return max(y2-(y+half_thickness),(y-half_thickness)-y2);
}

void main(){
    float raido_yx = iResolution.y / iResolution.x;
    vec2 center_vu =vec2(center.x,center.y*raido_yx);
    float radio = iResolution.y/iResolution.x;
    vec2 uv = raido_yx*2.0*(gl_FragCoord.xy / iResolution.xy-vec2(0.5,0.5));
    vec2 p1 = raido_yx*startPoint;
    vec2 p2 = raido_yx*endPoint;
    vec2 ptK = p1-p2;
    float k = ptK.y /ptK.x;
    float _distance = 0.0;
    vec2 vu =  uv-center_vu;
    if(startPoint.x==endPoint.x)
        _distance = lineSDF(vu.x,0.0,line_thickness);
    else
        _distance = lineSDF(vu.y,k*vu.x,line_thickness);
    float vt = 1.0- smoothstep(0.0,0.004,_distance);
    fragColor = vec4(color.xyz,color.w*vt);
//fragColor = color;
}