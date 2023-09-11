#version 130
in vec3 Position;
uniform vec3 Color;
uniform vec4 Ortho;
out vec4 vs_Color;
void main()
{
     gl_Position = vec4(
        2.0 * (Position.x - Ortho[0]) / (Ortho[1] - Ortho[0]) - 1,
        2.0 * (Position.y - Ortho[2]) / (Ortho[3] - Ortho[2]) - 1,
        Position.z,
        1.0
    );
     vs_Color = vec4(Color.x, Color.y, Color.z, 1.0);

}