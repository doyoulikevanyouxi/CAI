#version 330 core

//矩形中心
in vec2 center;
in vec2 size;
in vec4 color;
in float radius;

in float borderSize;
in vec4 borderColor;
//分辨率
uniform vec2 iResolution;
//输出
out vec4 fragColor;
//矩形SDF，目前不适用于圆形，后期会改进
//返回像素点到矩形的距离，在边上为0
float rectCircleSDF(vec2 pt,vec2 size,float radius){
    vec2 point = abs(pt);
    //调整需要被计算SDF矩形的大小
    vec2 half_size = size*0.5;
    //调整区域大小，当半径值大于任意大小时，认为该图形是一个圆形，那么被计算的矩形不在拥有大小
    if(radius >=half_size.x || radius >=half_size.y){
        half_size =vec2(0.0,0.0);
    }
    vec2 p_distance = point-half_size;
    float _distance = max(p_distance.x,p_distance.y);
    if(p_distance.x >0.0 && p_distance.y>0.0){
        _distance = length(p_distance);
    }
    return _distance - radius;
}

float circleSDF(vec2 pt,float radius){
    return length(pt)-radius;
}

void main(){
    //坐标从像素转换成成x,y单位坐标一致的标准设备坐标
    float raido_yx = iResolution.y / iResolution.x;
    vec2 vu = vec2(1.0,raido_yx)*2.0*(gl_FragCoord.xy/iResolution-vec2(0.5,0.5));
    vec2 center_vu =vec2(center.x,center.y*raido_yx);
    float edgeThickness = 0.0030;
    vec4 fColor = vec4(0.0,0.0,0.0,0.0);
    
    vec2 size_vu = vec2(size.x,size.y * raido_yx)+edgeThickness;
    //边框区域距离
    float _distance =0.0;
    if(radius <=0)
        _distance = rectCircleSDF(vu-center_vu,size_vu,radius);
    else
        _distance = rectCircleSDF(vu-center_vu,size_vu-borderSize*2.0-radius*2.0,radius+borderSize);
    //内部区域距离
    float _distance2 = rectCircleSDF(vu-center_vu,size_vu-borderSize*2.0-radius*2.0,radius);
    float vt1 = smoothstep(-edgeThickness,0.0,_distance);
    float vt2 = smoothstep(-edgeThickness,0.0,_distance2);
//    float vt3 = smoothstep();
    fragColor = vec4(color.xyz,color.w*(1-vt2))*(1.0-vt2)+vec4(borderColor.xyz,borderColor.w*(1.0-vt1))*vt2;
}