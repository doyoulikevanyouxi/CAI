#version 330 core

in vec4 vertexColor;
//ʹ�ø���ɫ��������Ҫһ��������ɫ������Ϊ����Ķ������������㣬������Ҫ�����ɾ���,���ü�����ɫ�����Ӷ������
out vec4 fragColor;
//�ֱ���
uniform mat4 projection_color; //��ɫͶӰ����
uniform vec2 iResolution;
//a��ʾ�ú�����x���꣬b��ʾy���꣬thickness��ʾ�ߵĿ�ȣ�edge_thickness��ʾƽ������
//�ú�����a,b��ʵ���������꣬���Ǹ�����a����Щ��Χ�ڵ�b���Ի��ƣ������ߵĶ����ں����ⶨ��
//ͬʱ��Ҫע�������������ĸ�����
float line(float a,float b,float thickness,float edge_thickness){
    float halfThickness = thickness*0.5;
    float halfbttom = smoothstep(a-halfThickness,a-halfThickness+edge_thickness,b);
    float halftop = smoothstep(a+halfThickness-edge_thickness,a+halfThickness,b);
    return halfbttom-halftop;
}

void main(){
	vec2 uv = vec2(1.0,iResolution.y/iResolution.x)*2.0*(gl_FragCoord.xy / iResolution-vec2(0.5,0.5));
    vec4 fColor =  projection_color * vertexColor;
    //����һ��б��Ϊ1��ֱ�ߣ����������Ӧ��������Ӧ�����ߵĺ�������ô�Ϳ��Ի�����
    //��Ϊ uv.y = uv.x;�����ز����������ʱ���Ͳ�����Ƴ�������Ҳ��������uv.y,sin(uv.x)��������������ʽ��������� sin(uv.x)�����yӦ���ڸõ��yֵ������������پͲ�����
    float line1 = line(uv.x,uv.y,0.01,0.01);
	fragColor = fColor*line1;
}