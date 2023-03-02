#include "NameEncode.h"

#include <ctype.h>

#define ESCAPE_SYMBOL_FIRST TEXT('_')
#define ESCAPE_SYMBOL_SECOND TEXT('h')
#define ESCAPE_SYMBOL TEXT("_h")
#define ESCAPE_SYMBOL_LEN 2
#define ESCAPE_END_SYMBOL TEXT('_')

#define ESCAPE_HEAD_NUMBER 0x01
#define ESCAPE_HEAD_NUMBER_SYMBOL TEXT("01")

#define ESCAPE_UNICODE_IDENT_LE TEXT('u')
#define ESCAPE_UNICODE_IDENT_BE TEXT('U')
#define ESCAPE_UNICODE_IDENT (IsLittleEndian() ? ESCAPE_UNICODE_IDENT_LE : ESCAPE_UNICODE_IDENT_BE)


static inline bool ShouldEscape(int C)
{
	return C <= 0x7F && !(::isalnum(C) || C == '_');
}

static inline bool IsLittleEndian()
{
	static struct V
	{
		V()
		{
			unsigned short N = 1;
			Bool = static_cast<bool>(reinterpret_cast<unsigned char*>(&N)[0]);
		}

		bool Bool;
	} Local;

	return Local.Bool;
}

static const char* HexList = "0123456789ABCDEF";

static inline void ByteToHex(uint8_t Value, TCHAR* Out)
{
	Out[0] = HexList[Value / 16];
	Out[1] = HexList[Value % 16];
}

static uint8 HexToByte(TCHAR Str)
{
	return Str >= 'A' ? Str - 'A' + 10 : Str - '0';
}

static uint8 HexToByte(const TCHAR* Str)
{
	return HexToByte(Str[0]) * 16 + HexToByte(Str[1]);
}

FString FNameEncode::Encode(const FString& Name, bool bEncodeWideString)
{
	constexpr int kNormal = 1;
	constexpr int kEscapeChar = 2;
	constexpr int kUnicodeString = 3;

	FString Ret;
	Ret.Reserve(Name.Len() + 4);
	
	const int LastIndex = Name.Len() - 1;

	int LastState = kNormal;

	for (int i = 0; i < Name.Len(); ++i)
	{
		const auto C = Name[i];

		if(C == ESCAPE_HEAD_NUMBER)
		{
			UE_LOG(LogTemp, Error, TEXT("string contains illegal characters: %s"), *Name);
			return {};
		}
		
		bool bEscapeSymbol = C == ESCAPE_SYMBOL_FIRST && i != LastIndex && Name[i + 1] == ESCAPE_SYMBOL_SECOND;
		bool bDigitHead = i == 0 && ::isdigit(C);

		if (bDigitHead)
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
			Ret.AppendChars(ESCAPE_HEAD_NUMBER_SYMBOL, 2);
			Ret.AppendChar(ESCAPE_END_SYMBOL);
			Ret.AppendChar(C);
			LastState = kEscapeChar;
		}
		else if (bEscapeSymbol || ShouldEscape(C))
		{
			Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
			TCHAR Hex[2];
			ByteToHex(C, Hex);
			Ret.AppendChars(Hex, 2);

			if (bEscapeSymbol) //skip escape symbol
			{
				++i;
			}

			Ret.AppendChar(ESCAPE_END_SYMBOL);
			LastState = kEscapeChar;
		}
		else if (bEncodeWideString && C > 0x7F)
		{
			if (LastState != kUnicodeString)
			{
				Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
				// add endian info
				Ret.AppendChar(ESCAPE_UNICODE_IDENT);
			}

			unsigned short _C = static_cast<unsigned short>(C);
			unsigned char* P = reinterpret_cast<unsigned char*>(&_C);

			TCHAR Hex[4];
			ByteToHex(P[0], Hex);
			ByteToHex(P[1], Hex + 2);

			Ret.AppendChars(Hex, 4);

			const bool bNext = bEncodeWideString && i != LastIndex && Name[i + 1] > 0x7F;
			if (bNext)
			{
				// next
			}
			else
			{
				Ret.AppendChar(ESCAPE_END_SYMBOL);
			}

			LastState = kUnicodeString;
		}
		else
		{
			// a-z A-Z 0-9 _
			Ret.AppendChar(C);
			LastState = kNormal;
		}
	}

	return Ret;
}

void FNameEncode::Encode(TArray<FString>& Names)
{
	for (auto& Name : Names)
	{
		Name = Encode(Name);
	}
}


FString FNameEncode::Decode(const FString& Name)
{
	constexpr int kNormal = 1;
	constexpr int kEscapeChar = 2;
	constexpr int kUnicodeString = 3;

	FString Ret;

	Ret.Reserve(Name.Len());
	const int LastIndex = Name.Len() - 1;

	int State = kNormal;

	bool UnicodeStringCtx_LE = true;
	bool UnicodeStringCtx_Collected = false;
	unsigned char UnicodeStringCtx_CollectedByte{};


	for (int i = 0; i < Name.Len(); ++i)
	{
		const auto C = Name[i];

		switch (State)
		{
		case kNormal:
			{
				const bool bEscape =
					C == ESCAPE_SYMBOL_FIRST &&
					i < LastIndex - 1 &&
					Name[i + 1] == ESCAPE_SYMBOL_SECOND;
				
				if (bEscape)
				{
					State = kEscapeChar;
					i += 1; // skip escape symbol
					break;
				}
				Ret.AppendChar(C);
			}
			break;

		case kEscapeChar:
			{
				if (C == ESCAPE_UNICODE_IDENT_LE || C == ESCAPE_UNICODE_IDENT_BE)
				{
					UnicodeStringCtx_LE = C == ESCAPE_UNICODE_IDENT_LE;
					State = kUnicodeString;
					break;
				}
				auto Hex = HexToByte(GetData(Name) + i);
				
				if (i == 2 /* hex start offset */ && Hex == ESCAPE_HEAD_NUMBER)
				{
					// do nothing.
				}
				else if (Hex == '_')
				{
					Ret.AppendChars(ESCAPE_SYMBOL, ESCAPE_SYMBOL_LEN);
				}
				else
				{
					Ret.AppendChar(Hex);
				}

				i += 2; //skip next char and end symbol
				State = kNormal;
			}
			break;

		case kUnicodeString:
			{
				if (i + 1 >= Name.Len())
				{
					UE_LOG(LogTemp, Error, TEXT("decode failed. %s"), *Name);
					return {};
				}

				unsigned char Byte = HexToByte(GetData(Name) + i);

				if (!UnicodeStringCtx_Collected)
				{
					UnicodeStringCtx_CollectedByte = Byte;
					UnicodeStringCtx_Collected = true;
					++i;
					break;
				}
				UnicodeStringCtx_Collected = false;

				short WideChar;
				unsigned char* P = reinterpret_cast<unsigned char*>(&WideChar);

				P[0] = UnicodeStringCtx_CollectedByte;
				P[1] = Byte;

				// endian mismatch
				if (IsLittleEndian() && !UnicodeStringCtx_LE)
				{
					const auto Temp = P[0];
					P[0] = P[1];
					P[1] = Temp;
				}

				++i;

				// peek next
				if (i != LastIndex && Name[i + 1] != ESCAPE_END_SYMBOL)
				{
					// next
					Ret.AppendChar(WideChar);
				}
				else
				{
					++i; //skip end symbol
					Ret.AppendChar(WideChar);
					State = kNormal;
				}
			}
			break;
		default: ;
		}
	}

	return Ret;
}

void FNameEncode::Decode(TArray<FString>& Names)
{
	for (auto& Name : Names)
	{
		Name = Decode(Name);
	}
}

/*
void FNameEncode::UnitTest()
{
	auto h0 = HexToByte(TEXT('A'));
	check(h0 == 10)

	auto h1 = HexToByte(TEXT('C'));
	check(h1 == 12)

	auto h2 = HexToByte(TEXT('3'));
	check(h2 == 3)

	auto h3 = HexToByte(TEXT("FF"));
	check(h3 == 255);

	TCHAR Char3[2];
	ByteToHex(TEXT('3'), Char3);
	check(Char3[0] == TEXT('3') && Char3[1] == TEXT('3'));

	FString v1s = TEXT("3DWidget");
	auto v1 = Encode(v1s);
	auto v1r = Decode(v1);
	check(v1s == v1r);

	FString v2s = TEXT("_h01_3DWidget");
	auto v2 = Encode(v2s);
	auto v2r = Decode(v2);
	check(v2s == v2r);

	FString v3s = TEXT("Anim");
	auto v3 = Encode(v3s);
	auto v3r = Decode(v3);
	check(v3s == v3r);

	FString v4s = TEXT("Anim-a");
	auto v4 = Encode(v4s);
	auto v4r = Decode(v4);
	check(v4s == v4r);

	FString v5s = TEXT("Anim_v1");
	auto v5 = Encode(v5s);
	auto v5r = Decode(v5);
	check(v5s == v5r);

	FString v6s = TEXT("Anim__v2");
	auto v6 = Encode(v6s);
	auto v6r = Decode(v6);
	check(v6s == v6r);

	FString v7s = TEXT("Anim___v3");
	auto v7 = Encode(v7s);
	auto v7r = Decode(v7);
	check(v7s == v7r);

	FString v8s = TEXT("IsCtrl?");
	auto v8 = Encode(v8s);
	auto v8r = Decode(v8);
	check(v8s == v8r);

	FString v9s = TEXT("get data_");
	auto v9 = Encode(v9s);
	auto v9r = Decode(v9);
	check(v9s == v9r);

	FString v10s = TEXT("技能3");
	auto v10 = Encode(v10s, true);
	auto v10r = Decode(v10);
	check(v10s == v10r);

	FString v11s = TEXT("+5/-*)(<>.!?#$%^&@");
	auto v11 = Encode(v11s);
	auto v11r = Decode(v11);
	check(v11s == v11r);

	FString v12s = TEXT("___啊___的___3__@_");
	auto v12 = Encode(v12s, true);
	auto v12r = Decode(v12);
	check(v12s == v12r);

	FString v13s = TEXT("___啊_h_h__h___hhhh_h-__hh@h__h@_");
	auto v13 = Encode(v13s, true);
	auto v13r = Decode(v13);
	check(v13s == v13r);
	
}
*/