#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
    //shader para fuente de luz, es el mismo cubito blanco en la misma posición
    //para simular la luz, para poder aplicar los efectos de luz al objeto que queremos
    //la fuente de luz por defecto no se pinta en la escena
    //los efectos de iluminacion está sobre el objeto, pero no sobre el cubito blanco
}