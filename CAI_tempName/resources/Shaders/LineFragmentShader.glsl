#version 330 core

in vec4 vertexColor;
//使用该着色器我们需要一个几何着色器，因为传入的顶点是两个顶点，我们需要将其变成矩形,利用几何着色器增加顶点输出
out vec4 fragColor;
//分辨率
uniform mat4 projection_color; //颜色投影矩阵
uniform vec2 iResolution;
//a表示该函数的x坐标，b表示y坐标，thickness表示线的宽度，edge_thickness表示平滑区间
//该函数的a,b其实并不是坐标，而是告诉在a的哪些范围内的b可以绘制，所以线的定义在函数外定义
//同时需要注意坐标是属于哪个坐标
float line(float a,float b,float thickness,float edge_thickness){
    float halfThickness = thickness*0.5;
    float halfbttom = smoothstep(a-halfThickness,a-halfThickness+edge_thickness,b);
    float halftop = smoothstep(a+halfThickness-edge_thickness,a+halfThickness,b);
    return halfbttom-halftop;
}

void main(){
	vec2 uv = vec2(1.0,iResolution.y/iResolution.x)*2.0*(gl_FragCoord.xy / iResolution-vec2(0.5,0.5));
    vec4 fColor =  projection_color * vertexColor;
    //这是一条斜率为1的直线，传入的坐标应该体现相应的曲线的函数，那么就可以画出来
    //因为 uv.y = uv.x;当像素不满足该条件时，就不会绘制出来，你也可以填入uv.y,sin(uv.x)或者其他函数形式，这里表面 sin(uv.x)计算的y应该在该点的y值附近，如果不再就不绘制
    float line1 = line(uv.x,uv.y,0.01,0.01);
	fragColor = fColor*line1;
}