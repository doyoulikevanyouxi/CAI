#version 330 core

//��������
in vec2 center;
in vec2 size;
in vec4 color;
in float radius;

//�ֱ���
uniform vec2 iResolution;
//���
out vec4 fragColor;
//����SDF��Ŀǰ��������Բ�Σ����ڻ�Ľ�
//�������ص㵽���εľ��룬�ڱ���Ϊ0
float rectSDF(vec2 pt,vec2 size,float radius){
    vec2 point = abs(pt);
    //������Ҫ������SDF���εĴ�С
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
    //���������ת���ɳ�x,y��λ����һ�µı�׼�豸����
    vec2 vu = vec2(1.0,iResolution.x / iResolution.y)*2.0*(gl_FragCoord.xy/iResolution-vec2(0.5,0.5));
//    if(radius <=0.0){
//        fragColor = color;
//        return;
//    }
    float edgeThickness = 0.005;
   
    vec2 size_vu = vec2(size.x,size.y * iResolution.x/iResolution.y)+edgeThickness;
    float _distance = rectSDF(vu-center,size_vu,radius);
    //������ݣ��õ��Ĳ�ֵ
    float vt =1.0 - smoothstep(-edgeThickness,0.0,_distance);
    //vt�õ�����һ����ֵ������Ӧ�õ�RGBA�е�A
    fragColor = color*vt;

}