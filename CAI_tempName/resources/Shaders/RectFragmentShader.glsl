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
float rectCircleSDF(vec2 pt,vec2 size,float radius){
    vec2 point = abs(pt);
    //������Ҫ������SDF���εĴ�С
    vec2 half_size = size*0.5;
    //���������С�����뾶ֵ���������Сʱ����Ϊ��ͼ����һ��Բ�Σ���ô������ľ��β���ӵ�д�С
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
    //���������ת���ɳ�x,y��λ����һ�µı�׼�豸����
    float raido_yx = iResolution.y / iResolution.x;
    vec2 vu = vec2(1.0,raido_yx)*2.0*(gl_FragCoord.xy/iResolution-vec2(0.5,0.5));
    vec2 center_vu =vec2(center.x,center.y*raido_yx);
    float edgeThickness = 0.0030;
    vec4 fColor = vec4(0.0,0.0,0.0,0.0);
    
    vec2 size_vu = vec2(size.x,size.y * raido_yx)+edgeThickness;
    //�߿��������
    float _distance =0.0;
    if(radius <=0)
        _distance = rectCircleSDF(vu-center_vu,size_vu,radius);
    else
        _distance = rectCircleSDF(vu-center_vu,size_vu-borderSize*2.0-radius*2.0,radius+borderSize);
    //�ڲ��������
    float _distance2 = rectCircleSDF(vu-center_vu,size_vu-borderSize*2.0-radius*2.0,radius);
    float vt1 = smoothstep(-edgeThickness,0.0,_distance);
    float vt2 = smoothstep(-edgeThickness,0.0,_distance2);
//    float vt3 = smoothstep();
    fragColor = vec4(color.xyz,color.w*(1-vt2))*(1.0-vt2)+vec4(borderColor.xyz,borderColor.w*(1.0-vt1))*vt2;
}