//struct VS_INPUT
//{
//  float3 m_Position : POSITION;
//};
//
//struct VS_OUTPUT
//{
//  float4 m_Position : SV_POSITION;
//};
//
//
//VS_OUTPUT main_VS(VS_INPUT vsInput)
//{
//  VS_OUTPUT output;
//  output.m_Position = float4(vsInput.m_Position, 1);
//  return output;
//}
//
//struct PS_INPUT
//{
//  float4 m_Position : SV_POSITION;
//
//};
//
//float4 main_PS(PS_INPUT Input) : SV_Target
//{
//  return float4(1.0f, 1.0f, 0.0f, 1.0f);
//}

float4 main_VS(float4 Pos : POSITION) : SV_POSITION
{
  return Pos;
}

float main_PS(float4 Pos : SV_POSITION) : SV_Target
{
  return float4(1.0f, 1.0f, 0.0f, 1.0f);
}

