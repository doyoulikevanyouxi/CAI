#version 330 core
//圆角矩形片段着色器原型
//CircleCorner函数是实现圆角的关键，该函数主要检查四角区域内的像素到
//相应圆心的距离是否在半径内。
out vec4 bgColor;
//这是分辨率
uniform vec2 uv_resolution;
uniform float radius;

//该圆角实现基于混合测试启用，实现对相应位置进行a值的平滑，如果不启用混合，将不会有效果
//在禁用混合下，想要实现圆角需要将smootstep替换成if判断，并使用discard语句丢弃像素点，
//此操作会产生锯齿，因此需要更多的操作来判定
//还有一个操作就是由两个矩形和四个圆形组合而成
float CircleCorner(vec2 point){
    float ra=0.005;
    if(point.x<(-0.5+radius)){
        if(point.y>(0.5-radius)){
            float ratio=1- smoothstep(0,ra,length(point-vec2(-0.5+radius,0.5-radius))-radius);
            return ratio;
        }
        if(point.y<(-0.5+radius)){
         float ratio=1- smoothstep(0,ra,length(point-vec2(-0.5+radius,-0.5+radius))-radius);
             return ratio;
        }
    }
    if(point.x>(0.5-radius)){
     if(point.y>(0.5-radius)){
     float ratio=1- smoothstep(0,ra,length(point-vec2(0.5-radius,0.5-radius))-radius);
            return ratio;
        }
        if(point.y<(-0.5+radius)){
         float ratio=1- smoothstep(0,ra,length(point-vec2(0.5-radius,-0.5+radius))-radius);
             return ratio;
        }
    }
    return 1;
}
void main(){
       vec2 px = 2*(gl_FragCoord.xy / uv_resolution -vec2(0.5,0.5));
       float ca= CircleCorner(px);

       bgColor = vec4(1.0, 0.0, 0.0, 1.0*ca);
}
