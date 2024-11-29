#version 330 core
//Բ�Ǿ���Ƭ����ɫ��ԭ��
//CircleCorner������ʵ��Բ�ǵĹؼ����ú�����Ҫ����Ľ������ڵ����ص�
//��ӦԲ�ĵľ����Ƿ��ڰ뾶�ڡ�
out vec4 bgColor;
//���Ƿֱ���
uniform vec2 uv_resolution;
uniform float radius;

//��Բ��ʵ�ֻ��ڻ�ϲ������ã�ʵ�ֶ���Ӧλ�ý���aֵ��ƽ������������û�ϣ���������Ч��
//�ڽ��û���£���Ҫʵ��Բ����Ҫ��smootstep�滻��if�жϣ���ʹ��discard��䶪�����ص㣬
//�˲����������ݣ������Ҫ����Ĳ������ж�
//����һ�������������������κ��ĸ�Բ����϶���
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
