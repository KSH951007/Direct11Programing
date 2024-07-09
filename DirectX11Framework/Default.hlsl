
struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

//정점 셰이더 단계 : 각 정점에 대해 정점 셰이더를 수행한다.
//버텍스 셰이더를 실행하는 주체는 GPU 가 실행한다
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position;
    output.color = input.color;
    
    return output;
}

//레스터라이저 단계 : 각 정점으로부터 픽셀 색상의 값을 보간하여 설정한다 그다음 픽셀셰이더로 넘어간다
//

//픽셀 셰이더 단계 : 조명이나 색상의 값을 만들어준다
//내부의 있는 모든 픽셀들을 대상으로 픽셀셰이더가 실행된다
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
}

