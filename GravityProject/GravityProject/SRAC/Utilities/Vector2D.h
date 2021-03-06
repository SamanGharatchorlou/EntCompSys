#pragma once

template<class T>
class Vector2D
{
public:
	Vector2D() { x = 0; y = 0; }
	Vector2D(T _x, T _y) : x(_x), y(_y) { }


	// -- Operators -- 

	// Operator +
	template<class K>
	inline Vector2D<T> operator + (Vector2D<K> vector) const
	{
		return Vector2D<T>(x + vector.x, y + vector.y);
	}

	template<class K>
	inline Vector2D<T> operator + (K scalar) const
	{
		return Vector2D<T>(x + scalar, y + scalar);
	}

	// Operator +=
	template<class K>
	inline Vector2D<T>& operator += (Vector2D<K> vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}

	// Operator -
	template<class K>
	inline Vector2D<T> operator - (Vector2D<K> vector) const
	{
		return Vector2D<T>(x - vector.x, y - vector.y);
	}

	template<class K>
	inline Vector2D<T> operator - (K scalar) const
	{
		return Vector2D<T>(x - scalar, y - scalar);
	}

	// Operator +=
	template<class K>
	inline Vector2D<T>& operator -= (Vector2D<K> vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}

	// Operator *
	template<class K>
	inline Vector2D<T> operator * (Vector2D<K> vector) const
	{
		return Vector2D<T>(x * vector.x, y * vector.y);
	}

	template<class K>
	inline Vector2D<T> operator * (K scalar) const
	{
		return Vector2D<T>((T)(x * scalar), (T)(y * scalar));
	}

	template<class K>
	inline Vector2D<T>& operator *= (Vector2D<K> vector)
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}

	template<class K>
	inline Vector2D<T>& operator *= (K scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Operator /
	template<class K>
	inline Vector2D<T> operator / (Vector2D<K> vector) const
	{
		return Vector2D<T>(x / vector.x, y / vector.y);
	}

	template<class K>
	inline Vector2D<T> operator / (K scalar) const
	{
		return Vector2D<T>(x / scalar, y / scalar);
	}

	template<class K>
	inline Vector2D<T>& operator /= (K scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}


	// Operator =
	template<class K>
	inline Vector2D<T>& operator = (Vector2D<K> vector)
	{
		x = (T)vector.x;
		y = (T)vector.y;
		return *this;
	}


	// Operator ==
	template<class K>
	inline bool operator == (Vector2D<K> vector) const
	{
		return (x == vector.x && y == vector.y);
	}

	
	// Operator !=
	template<class K>
	inline bool operator != (Vector2D<K> vector) const
	{
		return (x != vector.x || y != vector.y);
	}


	// -- Functions -- //

	inline Vector2D<int> toInt() const
	{
		return Vector2D<int>((int)x, (int)y);
	}

	inline Vector2D<float> toFloat() const
	{
		return Vector2D<float>((float)x, (float)y);
	}

	inline Vector2D<T>& zero() 
	{
		x = 0;
		y = 0;
		return *this;
	}

	inline Vector2D<T> normalise()
	{
		Vector2D<T> normalised = *this;

		if (x != 0 && y != 0)
		{
			T magnitude = std::sqrt((x * x) + (y * y));
			normalised = normalised / magnitude;
		}

		return normalised;
	}

	inline void set(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	inline bool isZero() const
	{
		return (x == 0.0f && y == 0.0f) ? true : false;
	}

	inline bool isPositive() const
	{
		return (x > 0.0f && y > 0.0f) ? true : false;
	}

	inline bool isNegative() const
	{
		return (x < 0.0f && y < 0.0f) ? true : false;
	}

	inline bool hasNegative() const
	{
		return (x < 0.0f || y < 0.0f) ? true : false;
	}

	inline T area() const
	{
		return x * y;
	}

	inline T magnitudeSquared() const
	{
		return (x * x) + (y * y);
	}

	inline T magnitude() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline T dotProduct(Vector2D<T> vector) const
	{
		return(x * vector.x + y * vector.y);
	}

	// members
	T x;
	T y;

};


// typedefs
typedef Vector2D<float>  VectorF;
using Index = Vector2D<int>;