董佩航第八次作业：
本次作业无法正常实现读取高度图，因为该项目MFC框架太过老旧，导致无法使用x64的OpenCV库来读取高程图数据
，因此没有合适的API来读取高程图纹理导入到项目中。
但是，一些其他关于顶点拓扑和纹理映射的函数已经实现。

void CSphereView::Show()
{
	// 生成顶点数据和纹理坐标数据
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			int index = y * 64 + x;

			// 设置顶点坐标
			vertices[index].x = x * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].y = y * planeSize / 63.0f - planeSize / 2.0f;
			vertices[index].z = 0.0f;

			// 设置纹理坐标
			texCoords[index].s = x * textureScale / 63.0f;
			texCoords[index].t = y * textureScale / 63.0f;
		}
	}

	// 生成索引数据
	int index = 0;
	for (int y = 0; y < 63; y++)
	{
		for (int x = 0; x < 63; x++)
		{
			int topLeft = y * 64 + x;
			int topRight = topLeft + 1;
			int bottomLeft = (y + 1) * 64 + x;
			int bottomRight = bottomLeft + 1;

			// 第一个三角形
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;

			// 第二个三角形
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
}
先使用这个函数在OpenGLView类中定义了一个平面，并且赋予了其顶点坐标，纹理坐标和索引信息。
void  CSphereView::DrawPlane()
{
	for (int i = 0; i < planeSize - 1;)
	{
		glBegin(GL_TRIANGLE_STRIP);
		{
			// 设置顶点位置和纹理
			glColor3f(0, 0, 0);
			GLubyte* pixels = new GLubyte[height_width * height_height * 3]; // 假设纹理大小为width x height，并且每个像素有3个字节（RGB格式）

			
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
在绘制时我们可以用这个函数来将所有顶点上的纹理坐标映射到我们的高程图纹理上灰度，然后再赋予给每个顶点其
Z值，最终绘制与每一个三角形。