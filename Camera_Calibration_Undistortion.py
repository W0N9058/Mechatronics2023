import cv2
import numpy as np
import os
from glob import glob

# 카메라 캘리브레이션 파라미터
fx = 463.153
fy = 457.514
cx = 286.336
cy = 232.420
k1 = -0.186771
k2 = 0.016192
p1 = -0.010891
p2 = 0.006875

# 왜곡 계수 배열 (k3 없음)
dist = np.array([k1, k2, p1, p2])

# 카메라 행렬
mtx = np.array([[fx, 0, cx],
                [0, fy, cy],
                [0, 0, 1]])

# 이미지 경로 설정
image_dir = "C:\\Users\\rigel\\Downloads\\saved_images\\saved_images"
image_paths = glob(os.path.join(image_dir, "*.jpg"))

for image_path in image_paths:
    # 이미지 읽기
    image = cv2.imread(image_path)

    if image is None:
        continue

    h, w = image.shape[:2]

    # 새로운 카메라 행렬 계산
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx,
                                                     dist,
                                                     (w, h),
                                                     1, (w, h))

    # 이미지 왜곡 보정
    dst = cv2.undistort(image, mtx, dist, None, newcameramtx)

    # ROI로 결과 자르기
    x, y, w, h = roi
    dst = dst[y:y+h, x:x+w]

    # 이미지 크기 조정
    image_resized = cv2.resize(image, (dst.shape[1], dst.shape[0]))

    # 원본 이미지와 왜곡 보정 이미지를 나란히 표시
    comparison = np.hstack((image_resized, dst))
    cv2.imshow('Comparison', comparison)
    cv2.waitKey(0)

cv2.destroyAllWindows()
