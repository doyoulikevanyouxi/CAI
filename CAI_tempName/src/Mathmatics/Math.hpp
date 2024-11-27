#pragma once
namespace Math {

	/// <summary>
	/// 矩阵模板 
	/// 使用的是行主序，与Opengl相反
	/// </summary>
	/// <typeparam name="R">矩阵行数</typeparam>
	/// <typeparam name="C">矩阵列数</typeparam>
	template<int R, int C>
	class Matrix {
	public:
		Matrix() noexcept {}
		Matrix(const Matrix& other) noexcept { memcpy(data, other.data, sizeof(float) * size); }
		Matrix(const float* data, int size) noexcept {
			setData(data, size);
		}
		
		Matrix(const std::initializer_list<float>& list) noexcept {
			int i = 0;
			for (auto& item : list) {
				if (i==size)
					break;
				data[i] = item;
				++i;
			}
		}

		/*Matrix(float... args)noexcept:Matrix(std::initializer_list<float>(arg...)) {
		}*/
		virtual ~Matrix() noexcept {}
	public:
		inline void setData(const float* value,int size) {
			memcpy(data, value, sizeof(float) * size);
		}
	public:
		inline constexpr int Rows() const noexcept { return rows; }
		inline constexpr int Colums() const noexcept { return colums; }
		inline constexpr int Size() const noexcept { return size; }
		std::string toString() const noexcept {
			std::string str;
			for (int i = 0; i < R; ++i) {
				str += "|";
				for (int j = 0; j < C; ++j) {
					str += std::to_string((*this)[i][j]) + " ";
				}
				str += "|\n";
			}
			return str;
		}
		//转置
		Matrix<C, R> Transpose() const noexcept {
			Matrix<C, R> tmp;
			for (int i = 0; i < R; ++i)
				for (int j = 0; j < C; ++j)
					tmp[j][i] = (*this)[i][j];
			return tmp;
		}
	public:
		Matrix& operator=(const Matrix& other) {
			memcpy(data, other.data, sizeof(float) * size);
			return *this;
		}

		Matrix& operator=(const std::initializer_list<float>& list) {
			int i = 0;
			for (auto& item : list) {
				if (i == size)
					break;
				data[i] = item;
				++i;
			}
			return *this;
		}

		float* operator[](int row) const {
			return data + row * colums;
		}

		Matrix operator+(const Matrix& other) {
			Matrix value(*this);
			for (int i = 0; i < R; ++i)
				for (int j = 0; j < C; ++j)
					value[i][j] += other[i][j];
			return value;
		}

		Matrix operator+(float arg) {
			Matrix value(*this);
			for (int i = 0; i < R; ++i)
				for (int j = 0; j < C; ++j)
					value[i][j] += arg;
			return value;
		}

		friend Matrix operator+(float arg, const Matrix& other) {
			Matrix value(other);
			for (int i = 0; i < R; ++i)
				for (int j = 0; j < C; ++j)
					value[i][j] += arg;
			return value;
		}
		template<int R2, int C2>
		Matrix<R,C2> operator*(const Matrix<R2, C2>& other) const {
			static_assert(C == R2, "matrix mutiplication require that first matrix's colums equals the second's rows");
			Matrix<R,C2> value;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < other.Colums(); ++j) {
					for (int k = 0; k < Colums(); ++k) {
						value[i][j] += (*this)[i][k] * other[k][j];
					}
				}
			}
			return value;
		}

		Matrix operator*(const float arg) {
			Matrix tmp(*this);
			for (int i = 0; i < rows; ++i)
				for (int j = 0; j < colums; ++j)
					tmp[i][j] *= arg;
			return tmp;
		}

		friend Matrix operator*(const float arg, Matrix& mt) {
			return mt * arg;
		}
	protected:
		static constexpr int rows = R;
		static constexpr int colums = C;
		static constexpr int size = R * C;
		mutable float data[size]{};
	};
	/// <summary>
	/// 矩阵的特殊类型--方阵
	/// </summary>
	/// <typeparam name="m">m为方阵的行</typeparam>
	template<int m>
	using SquareMatrix = Matrix<m, m>;
	using TransMatrix = Matrix<4, 4>;
	/// <summary>
	/// 具有3个分量的向量
	/// </summary>
	using vec3 = Matrix<3, 1>;
	/// <summary>
	/// 具有4个分量的向量
	/// </summary>
	using vec4 = Matrix<4, 1>;
	using vec4_t = Matrix<1, 4>;
	using vec2 = Matrix<2, 1>;
}
