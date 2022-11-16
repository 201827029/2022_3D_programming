#pragma once
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

class matrix3
{
public:


	float mat3[3][3] //행렬 생성
	{
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	float multiplemat3[3][3] // 곱한 값을 저장할 행렬 생성
	{
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};

	float transposetempmat3[3][3] //전치를 위한 빈 행렬 생성
	{
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};

	float transposetempmat3_2[3][3] //전치를 위한 빈 행렬 생성
	{
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};


	matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
	{
		mat3[0][0] = a; mat3[0][1] = b; mat3[0][2] = c;
		mat3[1][0] = d; mat3[1][1] = e; mat3[1][2] = f;
		mat3[2][0] = g; mat3[2][1] = h; mat3[2][2] = i;
	}

	matrix3(float x, float y, float z) // 이동
	{
		mat3[2][0] = x;
		mat3[2][1] = y;
		mat3[2][2] = z;
	}

	matrix3(float r, string s) // 회전
	{
		mat3[0][0] = cos(r * (3.14 / 180));
		mat3[0][1] = -sin(r * (3.14 / 180));
		mat3[1][0] = sin(r * (3.14 / 180));
		mat3[1][1] = cos(r * (3.14 / 180));
	}

	matrix3(float s, float ss) // 스케일
	{
		mat3[0][0] = s;
		mat3[1][1] = ss;
	}

	void identityMatrix() // 단위 행렬 초기화
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (i == j)
					mat3[i][j] = 1;
				else
					mat3[i][j] = 0;
			}
		}
	}

	void transposeMatrix3()
	{
		transposetempmat3[0][1] = mat3[0][1];
		transposetempmat3[0][2] = mat3[0][2];
		transposetempmat3[1][2] = mat3[1][2];

		transposetempmat3_2[1][0] = mat3[1][0];
		transposetempmat3_2[2][0] = mat3[2][0];
		transposetempmat3_2[2][1] = mat3[2][1];

		mat3[0][1] = transposetempmat3_2[1][0];
		mat3[0][2] = transposetempmat3_2[2][0];
		mat3[1][2] = transposetempmat3_2[2][1];

		mat3[1][0] = transposetempmat3[0][1];
		mat3[2][0] = transposetempmat3[0][2];
		mat3[2][1] = transposetempmat3[1][2];
	}

	matrix3 operator * (matrix3 mat3) //mat3 x mat3 연산자 오버로딩. 곱셈
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				multiplemat3[j][i] = 0;
				for (int k = 0; k < 3; k++)
				{
					multiplemat3[j][i] += this->mat3[j][k] * mat3.mat3[k][i];
				}
			}
		}
		return matrix3
		(multiplemat3[0][0], multiplemat3[0][1], multiplemat3[0][2],
			multiplemat3[1][0], multiplemat3[1][1], multiplemat3[1][2],
			multiplemat3[2][0], multiplemat3[2][1], multiplemat3[2][2]);
	}


	matrix3 operator + (matrix3 mat3) //mat3 + mat3 연산자 오버로딩. 덧셈
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				multiplemat3[j][i] = this->mat3[j][i] + mat3.mat3[j][i];
			}
		}
		return matrix3
		(multiplemat3[0][0], multiplemat3[0][1], multiplemat3[0][2],
			multiplemat3[1][0], multiplemat3[1][1], multiplemat3[1][2],
			multiplemat3[2][0], multiplemat3[2][1], multiplemat3[2][2]);
	}

	matrix3 operator - (matrix3 mat3) //mat3 - mat3 연산자 오버로딩. 뺄셈
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				multiplemat3[j][i] = this->mat3[j][i] - mat3.mat3[j][i];
			}
		}
		return matrix3
		(multiplemat3[0][0], multiplemat3[0][1], multiplemat3[0][2],
			multiplemat3[1][0], multiplemat3[1][1], multiplemat3[1][2],
			multiplemat3[2][0], multiplemat3[2][1], multiplemat3[2][2]);
	}

	void constantmat3(int a) //상수곱
	{
		mat3[0][0] *= a; mat3[0][1] *= a; mat3[0][2] *= a;
		mat3[1][0] *= a; mat3[1][1] *= a; mat3[1][2] *= a;
		mat3[2][0] *= a; mat3[2][1] *= a; mat3[2][2] *= a;
	}
	void divisionmat3(int a) //상수나눗셈
	{
		mat3[0][0] /= a; mat3[0][1] /= a; mat3[0][2] /= a;
		mat3[1][0] /= a; mat3[1][1] /= a; mat3[1][2] /= a;
		mat3[2][0] /= a; mat3[2][1] /= a; mat3[2][2] /= a;
	}
};

class vector3
{
public:

	vector3() { }
	float empty = 0;
	float vec3[1][3]  // 벡터값 저장될 곳
	{
		{0,0,1}
	};

	float vec3_2[1][3]  // 벡터와 행렬을 곱한 벡터값 저장될 곳
	{
		{0,0,1}
	};

	float result[1][3]	//곱한 값을 저장할 곳
	{
		{0,0,0}
	};

	vector3(float x, float y, float z) //x,y,z좌표를 받는다.
	{
		vec3[0][0] = x;
		vec3[0][1] = y;
		vec3[0][2] = z;
	}

	vector3 operator * (matrix3 mat) //연산자 오버로딩. 곱셈
	{

		for (int i = 0; i < 3; i++)
		{
			result[0][i] = 1;
			for (size_t j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					empty = empty + (vec3[0][k] * mat.mat3[k][j]);
				}
				result[0][j] = empty;
				empty = 0;
			}
		}
		/*vec3_2[0][0] = vec3[0][0] * mat.mat3[0][0] + vec3[0][1] * mat.mat3[1][0] + vec3[0][2] * mat.mat3[2][0];
		vec3_2[0][1] = vec3[0][0] * mat.mat3[0][1] + vec3[0][1] * mat.mat3[1][1] + vec3[0][2] * mat.mat3[2][1];
		vec3_2[0][2] = vec3[0][0] * mat.mat3[0][2] + vec3[0][1] * mat.mat3[1][2] + vec3[0][2] * mat.mat3[2][2];

		vec3[0][0] = vec3_2[0][0];
		vec3[0][1] = vec3_2[0][1];
		vec3[0][2] = vec3_2[0][2];*/

		//return vector3(vec3[0][0], vec3[0][1], vec3[0][2]);
		return vector3(result[0][0], result[0][1], result[0][2]);
	}

	void constantvec3(int a) // 상수 곱
	{
		vec3[0][0] *= a; vec3[0][1] *= a; vec3[0][2] *= a;
	}

	void divisionvec3(int a) // 상수 나눗셈
	{
		vec3[0][0] /= a; vec3[0][1] /= a; vec3[0][2] /= a;
	}
};

class matrix4
{

public:

	float mat4[4][4] //행렬 생성
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	float multiplemat4[4][4] // 곱한 값을 저장할 행렬 생성
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	float transposetempmat4[4][4] //전치를 위한 빈 행렬 생성
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	float transposetempmat4_2[4][4] //전치를 위한 빈 행렬 생성
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	matrix4(float x, float y, float z, float w) // xyz값
	{
		mat4[0][3] = x;
		mat4[1][3] = y;
		mat4[2][3] = z;
		mat4[3][3] = w;
	}
	matrix4(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p) // xyz값
	{
		mat4[0][0] = a; mat4[0][1] = b; mat4[0][2] = c; mat4[0][3] = d;
		mat4[1][0] = e; mat4[1][1] = f; mat4[1][2] = g; mat4[1][3] = h;
		mat4[2][0] = i; mat4[2][1] = j; mat4[2][2] = k; mat4[2][3] = l;
		mat4[3][0] = m; mat4[3][1] = n; mat4[3][2] = o; mat4[3][3] = p;
	}

	void identityMatrix4() // 단위 행렬 초기화
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (i == j)
					mat4[i][j] = 1;
				else
					mat4[i][j] = 0;
			}
		}
	}

	void transposeMatrix4()
	{
		transposetempmat4[0][1] = mat4[0][1];
		transposetempmat4[0][2] = mat4[0][2];
		transposetempmat4[0][3] = mat4[0][3];
		transposetempmat4[1][2] = mat4[1][2];
		transposetempmat4[1][3] = mat4[1][3];
		transposetempmat4[2][3] = mat4[2][3];

		transposetempmat4_2[1][0] = mat4[1][0];
		transposetempmat4_2[2][0] = mat4[2][0];
		transposetempmat4_2[2][1] = mat4[2][1];
		transposetempmat4_2[3][0] = mat4[3][0];
		transposetempmat4_2[3][1] = mat4[3][1];
		transposetempmat4_2[3][2] = mat4[3][2];

		mat4[0][1] = transposetempmat4_2[1][0];
		mat4[0][2] = transposetempmat4_2[2][0];
		mat4[0][3] = transposetempmat4_2[3][0];
		mat4[1][2] = transposetempmat4_2[2][1];
		mat4[1][3] = transposetempmat4_2[3][1];
		mat4[2][3] = transposetempmat4_2[3][2];

		mat4[1][0] = transposetempmat4[0][1];
		mat4[2][0] = transposetempmat4[0][2];
		mat4[2][1] = transposetempmat4[1][2];
		mat4[3][0] = transposetempmat4[0][3];
		mat4[3][1] = transposetempmat4[1][3];
		mat4[3][2] = transposetempmat4[2][3];
	}

	matrix4 operator * (matrix4 mat4) //mat4 x mat4 연산자 오버로딩. 곱셈
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				multiplemat4[j][i] = 0;
				for (int k = 0; k < 4; k++)
				{
					multiplemat4[j][i] += this->mat4[j][k] * mat4.mat4[k][i];
				}
			}
		}

		return matrix4
		(multiplemat4[0][0], multiplemat4[0][1], multiplemat4[0][2], multiplemat4[0][3],
			multiplemat4[1][0], multiplemat4[1][1], multiplemat4[1][2], multiplemat4[1][3],
			multiplemat4[2][0], multiplemat4[2][1], multiplemat4[2][2], multiplemat4[2][3],
			multiplemat4[3][0], multiplemat4[3][1], multiplemat4[3][2], multiplemat4[3][3]);
	}
	matrix4 operator + (matrix4 mat4) //mat4 + mat4 연산자 오버로딩. 덧셈
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				multiplemat4[j][i] = this->mat4[j][i] + mat4.mat4[j][i];
			}
		}
		return matrix4
		(multiplemat4[0][0], multiplemat4[0][1], multiplemat4[0][2], multiplemat4[0][3],
			multiplemat4[1][0], multiplemat4[1][1], multiplemat4[1][2], multiplemat4[1][3],
			multiplemat4[2][0], multiplemat4[2][1], multiplemat4[2][2], multiplemat4[2][3],
			multiplemat4[3][0], multiplemat4[3][1], multiplemat4[3][2], multiplemat4[3][3]);
	}

	matrix4 operator - (matrix4 mat4) //mat4 - mat4 연산자 오버로딩. 뺄셈
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				multiplemat4[j][i] = this->mat4[j][i] - mat4.mat4[j][i];
			}
		}
		return matrix4
		(multiplemat4[0][0], multiplemat4[0][1], multiplemat4[0][2], multiplemat4[0][3],
			multiplemat4[1][0], multiplemat4[1][1], multiplemat4[1][2], multiplemat4[1][3],
			multiplemat4[2][0], multiplemat4[2][1], multiplemat4[2][2], multiplemat4[2][3],
			multiplemat4[3][0], multiplemat4[3][1], multiplemat4[3][2], multiplemat4[3][3]);
	}

	void constantmat4(int a)
	{
		mat4[0][0] *= a; mat4[0][1] *= a; mat4[0][2] *= a; mat4[0][3] *= a;
		mat4[1][0] *= a; mat4[1][1] *= a; mat4[1][2] *= a; mat4[1][3] *= a;
		mat4[2][0] *= a; mat4[2][1] *= a; mat4[2][2] *= a; mat4[2][3] *= a;
		mat4[3][0] *= a; mat4[3][1] *= a; mat4[3][2] *= a; mat4[3][3] *= a;
	}
	void divisionmat4(int a)
	{
		mat4[0][0] /= a; mat4[0][1] /= a; mat4[0][2] /= a; mat4[0][3] /= a;
		mat4[1][0] /= a; mat4[1][1] /= a; mat4[1][2] /= a; mat4[1][3] /= a;
		mat4[2][0] /= a; mat4[2][1] /= a; mat4[2][2] /= a; mat4[2][3] /= a;
		mat4[3][0] /= a; mat4[3][1] /= a; mat4[3][2] /= a; mat4[3][3] /= a;
	}
};

class vector3_2
{
public:
	float vec31[3][1]
	{
		{0},
		{0},
		{1}
	};
	float vec31_2[3][1] // 전치되어 곱한 벡터값을 임시로 저장할 곳
	{
		{0},
		{0},
		{1}
	};
	float transposevec3[3][1] //전치한 수를 저장할 곳
	{
		{0},
		{0},
		{1}
	};

	float vec3[1][3]  // 벡터값 저장될 곳
	{
		{0,0,1}
	};

	float vec3_2[1][3]  // 벡터와 행렬을 곱한 벡터값 저장될 곳
	{
		{0,0,1}
	};

	vector3_2(float x, float y, float z) //x,y좌표를 받는다.
	{
		vec3[0][0] = x;
		vec3[0][1] = y;
		vec3[0][2] = z;
	}

	void transposeVec3()
	{
		transposevec3[0][0] = vec3[0][0];
		transposevec3[1][0] = vec3[0][1];
		transposevec3[2][0] = vec3[0][2];

		vec31[0][0] = transposevec3[0][0];
		vec31[1][0] = transposevec3[1][0];
		vec31[2][0] = transposevec3[2][0];
	}

	void identityVec3() // 단위 행렬 초기화
	{
		for (size_t i = 0; i < 3; i++)
		{
			vec3[0][i] = 1;
			vec31[0][i] = 1;
		}
	}
	vector3_2 operator * (matrix3 mat3) //31벡터와 33행렬 곱셈 연산자 오버로딩
	{
		vec31_2[0][0] = mat3.mat3[0][0] * vec31[0][0] + mat3.mat3[0][1] * vec31[1][0] + mat3.mat3[0][2] * vec31[2][0];
		vec31_2[1][0] = mat3.mat3[1][0] * vec31[0][0] + mat3.mat3[1][1] * vec31[1][0] + mat3.mat3[1][2] * vec31[2][0];
		vec31_2[2][0] = mat3.mat3[2][0] * vec31[0][0] + mat3.mat3[2][0] * vec31[1][0] + mat3.mat3[2][2] * vec31[2][0];

		vec31[0][0] = vec31_2[0][0];
		vec31[1][0] = vec31_2[1][0];
		vec31[2][0] = vec31_2[2][0];

		return vector3_2(vec31[0][0], vec31[1][0], vec31[2][0]);
	}
};

class vector4
{
public:
	float vec4[1][4]  // 벡터값 저장될 곳
	{
		{0,0,0,1}
	};

	float vec41[4][1]	//전치한 값을 저장할 곳
	{
		{0},
		{0},
		{0},
		{1}
	};

	vector4(float x, float y, float z, float w) //x,y좌표를 받는다.
	{
		vec4[0][0] = x;
		vec4[0][1] = y;
		vec4[0][2] = z;
		vec4[0][3] = w;
	}
	float vec4_2[1][4] // 14벡터와 44행렬 곱한 값을 저장할 곳
	{
		{0,0,0,1}
	};

	void transposeVec4() // 전치
	{
		for (size_t i = 0; i < 4; i++)
		{
			vec41[i][0] = vec4[0][i];
		}
	}

	void identityVec4() // 단위 행렬 초기화
	{
		for (size_t i = 0; i < 4; i++)
		{
			vec4[0][i] = 1;
			vec41[0][i] = 1;
		}
	}

	vector4 operator * (matrix4 mat4) //연산자 오버로딩. 곱셈
	{
		vec4_2[0][0] = vec4[0][0] * mat4.mat4[0][0] + vec4[0][1] * mat4.mat4[1][0] + vec4[0][2] * mat4.mat4[2][0] + vec4[0][3] * mat4.mat4[3][0];
		vec4_2[0][1] = vec4[0][0] * mat4.mat4[0][1] + vec4[0][1] * mat4.mat4[1][1] + vec4[0][2] * mat4.mat4[2][1] + vec4[0][3] * mat4.mat4[3][1];
		vec4_2[0][2] = vec4[0][0] * mat4.mat4[0][2] + vec4[0][1] * mat4.mat4[1][2] + vec4[0][2] * mat4.mat4[2][2] + vec4[0][3] * mat4.mat4[3][2];
		vec4_2[0][3] = vec4[0][0] * mat4.mat4[0][3] + vec4[0][1] * mat4.mat4[1][3] + vec4[0][2] * mat4.mat4[2][3] + vec4[0][3] * mat4.mat4[3][3];

		vec4[0][0] = vec4_2[0][0];
		vec4[0][1] = vec4_2[0][1];
		vec4[0][2] = vec4_2[0][2];
		vec4[0][3] = vec4_2[0][3];

		return vector4(vec4[0][0], vec4[0][1], vec4[0][2], vec4[0][3]);
	}

	void constantvec4(int a)
	{
		vec4[0][0] *= a; vec4[0][1] *= a; vec4[0][2] *= a; vec4[0][3] *= a;
	}
	void divisionvec4(int a)
	{
		vec4[0][0] /= a; vec4[0][1] /= a; vec4[0][2] /= a; vec4[0][3] /= a;
	}
};

class vector4_2
{
public:
	float vec4[1][4]  // 벡터값 저장될 곳
	{
		{0,0,0,1}
	};

	float vec41_2[4][1]	 //전치한 값을 저장할 곳
	{
		{0},
		{0},
		{0},
		{1}
	};
	float tempvec41[4][1]	//44행렬과 41벡터 곱한 값을 저장할 곳
	{
		{0},
		{0},
		{0},
		{1}
	};

	float transposevec41[4][1] //44행렬과 41벡터 곱한 값을 임시로 저장할 곳
	{
		{0},
		{0},
		{0},
		{1}
	};

	vector4_2(float x, float y, float z, float w) //x,y좌표를 받는다.
	{
		vec4[0][0] = x;
		vec4[0][1] = y;
		vec4[0][2] = z;
		vec4[0][3] = w;
	}
	float vec4_2[1][4] // 14벡터와 44행렬 곱한 값을 저장할 곳
	{
		{0,0,0,1}
	};

	void transposeVec4_2() // 전치
	{
		for (size_t i = 0; i < 4; i++)
		{
			vec41_2[i][0] = vec4[0][i];
		}
	}
	vector4_2 operator * (matrix4 mat4)
	{
		transposevec41[0][0] = mat4.mat4[0][0] * vec41_2[0][0] + mat4.mat4[0][1] * vec41_2[1][0] + mat4.mat4[0][2] * vec41_2[2][0] + mat4.mat4[0][3] * vec41_2[3][0];
		transposevec41[1][0] = mat4.mat4[1][0] * vec41_2[0][0] + mat4.mat4[1][1] * vec41_2[1][0] + mat4.mat4[1][2] * vec41_2[2][0] + mat4.mat4[1][3] * vec41_2[3][0];
		transposevec41[2][0] = mat4.mat4[2][0] * vec41_2[0][0] + mat4.mat4[2][1] * vec41_2[1][0] + mat4.mat4[2][2] * vec41_2[2][0] + mat4.mat4[2][3] * vec41_2[3][0];
		transposevec41[3][0] = mat4.mat4[3][0] * vec41_2[0][0] + mat4.mat4[3][1] * vec41_2[1][0] + mat4.mat4[3][2] * vec41_2[2][0] + mat4.mat4[3][3] * vec41_2[3][0];

		vec41_2[0][0] = transposevec41[0][0];
		vec41_2[1][0] = transposevec41[1][0];
		vec41_2[2][0] = transposevec41[2][0];
		vec41_2[3][0] = transposevec41[3][0];

		return vector4_2(vec41_2[0][0], vec41_2[1][0], vec41_2[2][0], vec41_2[3][0]);
	}
};