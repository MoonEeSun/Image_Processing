#include "main.h"

void ImageCreate(Img_Buf *img, Int picSize)
{
	FILE* fp;

	fopen_s(&fp, "lena_512x512.raw", "rb"); //���� ���� ����
	img->ori = (UChar*)malloc(sizeof(UChar) * picSize); //���� ���� ũ�⸸ŭ ���� ����
	img->rec = (UChar*)malloc(sizeof(UChar) * picSize); //��� ���� ũ�⸸ŭ ���� ����

	memset(img->ori, 0, sizeof(UChar) * picSize); //0���� �ʱ�ȭ
	fread(img->ori, sizeof(UChar), picSize, fp); // ���� ���� �б�(���� ������ �ȼ� ���� �迭 ������ ����)

	fclose(fp);
}

void ImageOutput(Img_Buf* img, Int picSize)
{
	FILE* fp;

	fopen_s(&fp, "Rec_DFT.raw", "wb"); //��� ���� ���� ����
	
	fwrite(img->rec, sizeof(UChar), picSize, fp); // ���� ���� �б�(���� ������ �ȼ� ���� �迭 ������ ����)

	fclose(fp);
	free(img->ori);
	free(img->rec);
}

void main()
{
	
	Img_Buf img; // ��������� ���������� ���۸� �����ϴ� ����

	Int wid = WIDTH; Int hei = HEIGHT;
	Int min = minVal; Int max = maxVal;

	Int picSize = wid * hei; //���� ������


	DFT_Val DFT;
	clock_t start, end; // �ð��ʸ� ���� ���� ����
	float res;

	ImageCreate(&img, picSize); // �������� �о����

	start = clock(); // �ð��� ����
	DFT_Process (&img, &DFT);
	IDFT_Process(&img, &DFT);
	PSNR(&img); // MSE, PSNR ���
	end = clock(); // �ð��� ��
	res = (float)(end - start) / CLOCKS_PER_SEC; // �ҿ�� �ð� ���
	ImageOutput(&img, picSize); // ���� ���� ���

	printf("\nDFT �ҿ�� �ð� : %.3f \n", res);
	printf("start = %d \n", start);
	printf("end   = %d \n", end);

	printf("\n\n\n");

	
}

void PSNR(Img_Buf* img)
{
	Int i, j;
	Int wid = WIDTH; Int hei = HEIGHT;
	Double mse = 0, psnr = 0, max = 0;
	UChar Img1 = 0, Img2 = 0;

	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			Img1 = img->ori[i * wid + j];
			Img2 = img->rec[i * wid + j];

			mse += ((Img1 - Img2) * (Img1 - Img2));
			if (Img1 > max)
				max = Img1;
		}
	}

	mse = mse / (wid * hei);
	printf("MSE : %lf\n", mse);
	psnr = 20 * log10(max / sqrt(mse));
	printf("PSNR : %lf\n", psnr);

	if (mse == 0)
		printf("\n���� ��ġ\n");
	else
		printf("\n���� ����ġ\n");
}