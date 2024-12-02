#version 330 core
in vec2 center;
in vec2 size;
in vec4 color;
in vec2 startPoint;
in vec2 endPoint;
in float line_thickness;
//ʹ�ø���ɫ��������Ҫһ��������ɫ������Ϊ����Ķ������������㣬������Ҫ�����ɾ���,���ü�����ɫ�����Ӷ������

//�ֱ���
uniform vec2 iResolution;
out vec4 fragColor;

//a��ʾ�ú�����x���꣬b��ʾy���꣬thickness��ʾ�ߵĿ�ȣ�edge_thickness��ʾƽ������
//�ú�����a,b��ʵ���������꣬���Ǹ�����a����Щ��Χ�ڵ�b���Ի��ƣ������ߵĶ����ں����ⶨ��
//ͬʱ��Ҫע�������������ĸ�����
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