���庽�ڰ˴���ҵ��
������ҵ�޷�����ʵ�ֶ�ȡ�߶�ͼ����Ϊ����ĿMFC���̫���Ͼɣ������޷�ʹ��x64��OpenCV������ȡ�߳�ͼ����
�����û�к��ʵ�API����ȡ�߳�ͼ�����뵽��Ŀ�С�
���ǣ�һЩ�������ڶ������˺�����ӳ��ĺ����Ѿ�ʵ�֡�

void CSphereView::Show()
{
	// ���ɶ������ݺ�������������
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			int index = y * 64 + x;

			// ���ö�������
			vertices[index].x = x * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].y = y * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].z = 0.0f;

			// ������������
			texCoords[index].s = x * textureScale / 63.0f;
			texCoords[index].t = y * textureScale / 63.0f;
		}
	}

	// ������������
	int index = 0;
	for (int y = 0; y < 63; y++)
	{
		for (int x = 0; x < 63; x++)
		{
			int topLeft = y * 64 + x;
			int topRight = topLeft + 1;
			int bottomLeft = (y + 1) * 64 + x;
			int bottomRight = bottomLeft + 1;

			// ��һ��������
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;

			// �ڶ���������
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
}
��ʹ�����������OpenGLView���ж�����һ��ƽ�棬���Ҹ������䶥�����꣬���������������Ϣ��
void  CSphereView::DrawPlane()
{
	for (int i = 0; i < planeSize - 1;)
	{
		glBegin(GL_TRIANGLE_STRIP);
		{
			// ���ö���λ�ú�����
			glColor3f(0, 0, 0);
			GLubyte* pixels = new GLubyte[height_width * height_height * 3]; // ���������СΪwidth x height������ÿ��������3���ֽڣ�RGB��ʽ��

			
			glTexImage2D(GL_TEXTURE_2D, 0, 3, height_height,
				height_width, 0, GL_RGB, GL_UNSIGNED_BYTE,pixels);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			GLubyte red = pixels[(int)(vertices[indices[i]].s* 64/height_width +
				vertices[indices[i]].t* 64/height_height) *3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y, red);
			i++;
			red=pixels[(int)(vertices[indices[i]].s * 64 / height_width +
				vertices[indices[i]].t * 64 / height_height) * 3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y,red);
			i++;
			red=pixels[(int)(vertices[indices[i]].s * 64 / height_width +
				vertices[indices[i]].t * 64 / height_height) * 3];
			glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y, red);
			i++;
		}
		glEnd();

	}
}
�ڻ���ʱ���ǿ�������������������ж����ϵ���������ӳ�䵽���ǵĸ߳�ͼ�����ϻҶȣ�Ȼ���ٸ����ÿ��������
Zֵ�����ջ�����ÿһ�������Ρ�