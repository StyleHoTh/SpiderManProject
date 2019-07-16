// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class UTDMathLibrary
{
public:

	//�������������߷�����ָ������ļнǡ���Χ��-180��180��
	static float CalcDegreeFromDirection(const FVector& SrcLoc, const FVector& DestLoc, const FRotator& RelatedRot);

	//����A������B����ļнǡ���Χ��-180��180��
	static float CalcDegreeFromDirection(const FVector& Direction, const FRotator& RelatedRot);

	static bool IsInRecRange(const FVector& OrignLoc,const FVector& OrignDir,const FVector& TargetLoc,const float LocX,const float LocY,const float LengthX,const float LengthY,const float HightZ);
	static bool IsInCylRange(const FVector& OrignLoc,const FVector& OrignDir,const FVector& TargetLoc,const float LocX,const float LocY,const float CircleR,const float HightZ);
	static bool IsInSectorRange(const FVector& OrignLoc,const FVector& OrignDir,const FVector& TargetLoc,const float SectorR,const float SectorAngle,const float HightZ);
	static bool IsInSphereRange(const FVector& OrignLoc,const FVector& OrignDir,const FVector& TargetLoc,const float SphereR);

	static float CacluAngleBetweenToAngle(float ang1, float ang2);

	static FVector CalcOffsetLocAfterRotator(FVector Offset, FVector RotatorVec);
};

