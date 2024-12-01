#version 330 core

//��������
in vec2 center;
in vec2 size;
in vec4 color;
in float radius;

in float borderSize;
in vec4 borderColor;
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
    vec2 center_vu =vec2(center.x,center.y*iResolution.x / iResolution.y);
    float edgeThickness = 0.0035;
    vec2 size_vu = vec2(size.x,size.y * iResolution.x/iResolution.y)+edgeThickness;
    float _distance = rectSDF(vu-center_vu,size_vu,radius);
    float _distance2 = rectSDF(vu-center_vu,size_vu-borderSize,radius-borderSize);
    float vm = _distance-_distance2;
    float vt1 = smoothstep(-edgeThickness,0.0,_distance2);
    float vt2 = smoothstep(-edgeThickness,0.0,_distance);
    fragColor = mix(vec4(color.xyz,color.w*(1.0-vt1)),vec4(borderColor.xyz,borderColor*(1.0-vt2)),vt1);
}