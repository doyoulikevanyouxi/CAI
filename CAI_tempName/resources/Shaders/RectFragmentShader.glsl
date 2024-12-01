#version 330 core

//矩形中心
in vec2 center;
in vec2 size;
in vec4 color;
in float radius;

//分辨率
uniform vec2 iResolution;
//输出
out vec4 fragColor;
//矩形SDF，目前不适用于圆形，后期会改进
//返回像素点到矩形的距离，在边上为0
float rectSDF(vec2 pt,vec2 size,float radius){
    vec2 point = abs(pt);
    //调整需要被计算SDF矩形的大小
    vec2 ac_size = size-radius*2.0;
    vec2 half_size = ac_size*0.5;
    vec2 p_distance = point-half_size;
    float _distance = max(p_distance.x,p_distance.y);
    if(p_distance.x >0.0 && p_distance.y>0.0){
        _distance = length(point-half_size);
    }
    return _distance - radius;
}

void main(){
    //坐标从像素转换成成x,y单位坐标一致的标准设备坐标
    vec2 vu = vec2(1.0,iResolution.x / iResolution.y)*2.0*(gl_FragCoord.xy/iResolution-vec2(0.5,0.5));
//    if(radius <=0.0){
//        fragColor = color;
//        return;
//    }
    float edgeThickness = 0.005;
   
    vec2 size_vu = vec2(size.x,size.y * iResolution.x/iResolution.y)+edgeThickness;
    float _distance = rectSDF(vu-center,size_vu,radius);
    //消除锯齿，得到的插值
    float vt =1.0 - smoothstep(-edgeThickness,0.0,_distance);
    //vt得到的是一个插值，可以应用到RGBA中的A
    fragColor = color*vt;

}