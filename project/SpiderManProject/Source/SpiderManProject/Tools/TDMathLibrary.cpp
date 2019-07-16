// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMathLibrary.h"
//#include "Unreal/Character/BaseCharacter.h"
//#include "Unreal/Manager/WidgetManager.h"
//#include "Unreal/UI/BaseUI.h"

float UTDMathLibrary::CalcDegreeFromDirection(const FVector& SrcLoc, const FVector& DestLoc, const FRotator& RelatedRot)
{
	FVector Direction = DestLoc - SrcLoc;
	return CalcDegreeFromDirection(Direction, RelatedRot);
}

float UTDMathLibrary::CalcDegreeFromDirection(const FVector& Direction, const FRotator& RelatedRot)
{
	FMatrix RotMatrix = FRotationMatrix(RelatedRot);
	FVector ForwardVec = RotMatrix.GetScaledAxis(EAxis::X);
	FVector RightVec = RotMatrix.GetScaledAxis(EAxis::Y);
	FVector Normal = Direction.GetSafeNormal2D();

	float ForwardCosAngle = FVector::DotProduct(ForwardVec, Normal);
	float ForwardDelDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

	float RightCosAngle = FVector::DotProduct(RightVec, Normal);
	if (RightCosAngle < 0)
	{
		ForwardDelDegree *= -1;
	}

	return ForwardDelDegree;
}


bool UTDMathLibrary::IsInRecRange(const FVector& OrignLoc /*�������ĵ�*/, const FVector& OrignDir /*�������ĵ㳯��*/, const FVector& TargetLoc/*�ж϶�������*/, const float LocX /*��������ǰ��ƫ��*/, const float LocY /*���������ҷ�ƫ��*/, const float LengthX /*���Y�����ܳ���*/, const float LengthY /*���X�����ܳ���*/, const float HightZ /*�߶�*/)
{
	//�������������Ķ�����Զ������һ�μ���
	const float VecX1 = LocX - LengthY / 2.f;
	const float VecX2 = LocX + LengthY / 2.f;
	const float VecY1 = LocY - LengthX / 2.f;
	const float VecY2 = LocY + LengthX / 2.f;

	const float Xmax = LocX > 0 ? VecX2 : VecX1;
	const float Ymax = LocY > 0 ? VecY2 : VecY1;
	const float DisSqu = Xmax * Xmax + Ymax * Ymax;

	if (FVector::DistSquared(OrignLoc, TargetLoc) > DisSqu)
	{
		return false;
	}

	FTransform OrignTrans = FTransform(OrignDir.Rotation(), OrignLoc);
	FVector LocalLoc = OrignTrans.InverseTransformPosition(TargetLoc);

	if (LocalLoc.X > VecX1 && LocalLoc.X<VecX2 && LocalLoc.Y>VecY1 && LocalLoc.Y < VecY2 && abs(LocalLoc.Z) < abs(HightZ / 2.f))
	{
		return true;
	}

	return false;
}

bool UTDMathLibrary::IsInCylRange(const FVector& OrignLoc /*�������ĵ�*/, const FVector& OrignDir /*�������ĵ㳯��*/, const FVector& TargetLoc/*�ж϶�������*/, const float LocX /*��������ǰ��ƫ��*/, const float LocY /*���������ҷ�ƫ��*/, const float CircleR /*�뾶*/, const float HightZ /*�߶�*/)
{
	//����Բ����
	float Xmax = LocX >= 0.f ? LocX + CircleR : LocX - CircleR;
	float Ymax = LocY >= 0.f ? LocY + CircleR : LocY - CircleR;
	const float DisSqu = Xmax * Xmax + Ymax * Ymax;
	if (FVector::DistSquared(OrignLoc, TargetLoc) > DisSqu)
	{
		return false;
	}

	FTransform OrignTrans = FTransform(OrignDir.Rotation(), OrignLoc);
	FVector LocalLoc = OrignTrans.InverseTransformPosition(TargetLoc);

	if ((LocalLoc.X - LocX)*(LocalLoc.X - LocX) + (LocalLoc.Y - LocY)*(LocalLoc.Y - LocY) < CircleR*CircleR)
	{
		if (abs(LocalLoc.Z) < abs(HightZ / 2.f))
		{
			return true;
		}
	}

	return false;
}

bool UTDMathLibrary::IsInSectorRange(const FVector& OrignLoc /*�������ĵ�*/, const FVector& OrignDir /*�������ĵ㳯��*/, const FVector& TargetLoc/*�ж϶�������*/, const float SectorR /*�뾶*/, const float SectorAngle /*�Ƕ�*/, const float HightZ /*�߶�*/)
{
	//�жϸ߶�
	if (abs(TargetLoc.Z - OrignLoc.Z) > HightZ / 2.f)
	{
		return false;
	}

	FVector2D TarLoc = FVector2D(TargetLoc.X, TargetLoc.Y);
	FVector2D OriLoc = FVector2D(OrignLoc.X, OrignLoc.Y);

	//��Բ����
	if (FVector2D::DistSquared(OriLoc, TarLoc) > SectorR * SectorR)
	{
		return false;
	}

	//ת�����ֲ��ռ������ϸ����
	FTransform OrignTrans = FTransform(OrignDir.Rotation(), OrignLoc);
	FVector LocalLoc = OrignTrans.InverseTransformPosition(TargetLoc);
	FVector2D VecX(1.f, 0);
	FVector2D VecLoc(LocalLoc.X, LocalLoc.Y);
	float angle = FMath::RadiansToDegrees(acosf(FVector2D::DotProduct(VecX, VecLoc.GetSafeNormal())));

	if (abs(angle) < SectorAngle / 2.f)
	{
		return true;
	}
	return false;
}

bool UTDMathLibrary::IsInSphereRange(const FVector& OrignLoc /*�������ĵ�*/, const FVector& OrignDir /*�������ĵ㳯��*/, const FVector& TargetLoc/*�ж϶�������*/, const float SphereR /*�뾶*/)
{
	if (FVector::DistSquared(OrignLoc, TargetLoc) < (SphereR*SphereR))
	{
		return true;
	}
	return false;
}

float UTDMathLibrary::CacluAngleBetweenToAngle(float ang1, float ang2)
{
	float angerr = ang1 - ang2;
	if (angerr > 180.f)
	{
		return 360.f - angerr;
	}
	else if (angerr < -180.f)
	{
		return angerr + 360.f;
	}
	return abs(angerr);
}

FVector UTDMathLibrary::CalcOffsetLocAfterRotator(FVector Offset, FVector RotatorVec)
{
	float BaseDenominator = FMath::Sqrt(RotatorVec.X * RotatorVec.X + RotatorVec.Y * RotatorVec.Y);
	float LocX = (Offset.X * RotatorVec.X - Offset.Y * RotatorVec.Y) / BaseDenominator;
	float LocY = (Offset.Y * RotatorVec.X + Offset.X * RotatorVec.Y)/ BaseDenominator;
	return FVector(LocX, LocY, Offset.Z);
}