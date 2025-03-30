import pickle
import cv2
import os

# 데이터 파일 경로
file_path = r'C:\Users\rigel\Downloads\data1.pkl'  # 적절한 경로로 변경하세요

# 데이터 로드 함수
def load_data(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = pickle.load(f)
        print(f"Data loaded from {file_path}")
        print(f"Number of data points: {len(data)}")
        return data
    except Exception as e:
        print(f"Failed to load data from {file_path}: {e}")
        return None

# 이미지 시각화 및 조향값 출력 함수
def display_data(data, num_samples=5):
    for i, entry in enumerate(data[:num_samples]):
        image = entry['images']
        angle = entry['int_values']
        cv2.imshow(f"Image {i}", image)
        print(f"Image {i} - Steering angle: {angle}")
        cv2.waitKey(0)  # 키 입력을 기다립니다.
        cv2.destroyAllWindows()

if __name__ == "__main__":
    data = load_data(file_path)
    if data is not None:
        display_data(data)