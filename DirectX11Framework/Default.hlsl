
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

//���� ���̴� �ܰ� : �� ������ ���� ���� ���̴��� �����Ѵ�.
//���ؽ� ���̴��� �����ϴ� ��ü�� GPU �� �����Ѵ�
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position;
    output.color = input.color;
    
    return output;
}

//�����Ͷ����� �ܰ� : �� �������κ��� �ȼ� ������ ���� �����Ͽ� �����Ѵ� �״��� �ȼ����̴��� �Ѿ��
//

//�ȼ� ���̴� �ܰ� : �����̳� ������ ���� ������ش�
//������ �ִ� ��� �ȼ����� ������� �ȼ����̴��� ����ȴ�
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
}

