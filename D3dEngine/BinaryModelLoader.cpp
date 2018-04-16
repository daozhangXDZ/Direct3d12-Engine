#include "stdafx.h"
#include "BinaryModelLoader.h"
#include <sys/stat.h>

/**
 * @brief Construct a new Binary Model Loader:: Binary Model Loader object
 *		Loads a coxl model file from a given path
		Can only use the coxl file format as it uses the formal given to it from the Model2CoxlLoader
 * 
 * @param filePath the path to the file which is being loaded
 * @param hasAnimations whether the file has animation (so the correct data can be loaded)
 */
BinaryModelLoader::BinaryModelLoader(const char* filePath, bool hasAnimations)
{
	// open file
	std::ifstream input;
	input.open(filePath, std::ios::binary);
	input.seekg(0, std::ios::beg);
	auto size_tSize = sizeof(size_t);
	// init the variables which represent the number of items in the corresponding array from the file
	size_t indsSize = 0;
	size_t vertsSize = 0;
	size_t animsCount = 0;
	size_t boneCountsCount = 0;
	size_t frameCountsCount = 0;
	std::vector<size_t> boneCounts;
	auto frameCounts = std::vector<std::vector<size_t>>();

	// Load the sizes 
	input.read(reinterpret_cast<char*>(&vertsSize), size_tSize);
	input.read(reinterpret_cast<char*>(&indsSize), size_tSize);
	input.read(reinterpret_cast<char*>(&animsCount), size_tSize);
	input.read(reinterpret_cast<char*>(&boneCountsCount), size_tSize);
	input.read(reinterpret_cast<char*>(&frameCountsCount), size_tSize);
	boneCounts = std::vector<size_t>(boneCountsCount);
	input.read(reinterpret_cast<char*>(boneCounts.data()), boneCountsCount * size_tSize);

	// load the bones sizes
	for (auto i = 0; i < boneCounts.size(); i++) {
		auto bones = boneCounts[i];
		frameCounts.push_back(std::vector<size_t>(bones));
		input.read(reinterpret_cast<char*>(frameCounts[i].data()), bones * size_tSize);
	}

	// get vertices
	auto verticesVector = std::make_shared<std::vector<Structures::VertexTexCoordNormal>>(vertsSize);
	auto verticesBufferSize = vertsSize * sizeof Structures::VertexTexCoordNormal;
	input.read(reinterpret_cast<char*>(verticesVector->data()), verticesBufferSize);

	// get indices
	auto indicesVector = std::make_shared<std::vector<unsigned long>>(indsSize);
	auto indicesBufferSize = indsSize * sizeof(unsigned long);
	input.read(reinterpret_cast<char*>(indicesVector->data()), indicesBufferSize);

	// get animations
	auto animations = std::make_shared<std::vector<std::vector<std::vector<XMMATRIX>>>>();
	if (hasAnimations) {
		for (auto i = 0; i < animsCount; i++) {
			auto animation = std::vector<std::vector<XMMATRIX>>();
			animation.reserve(boneCounts[i]);
			for (auto frameCount : frameCounts[i]) {
				auto frames = std::vector<XMFLOAT4X4>(frameCount);
				input.read(reinterpret_cast<char*>(frames.data()), frameCount * sizeof(XMFLOAT4X4));
				auto newFrames = std::vector<XMMATRIX>();
				newFrames.reserve(frameCount);
				for (auto frame : frames) {
					newFrames.push_back(XMLoadFloat4x4(&frame));
				}
				animation.push_back(newFrames);
			}
			animations->push_back(animation);
		}
	}

	// close and return the file and its data
	input.close();
	m_finalData = std::make_unique<Structures::VerticesIndicesFromBin>();
	m_finalData->vertices = verticesVector;
	m_finalData->indices = indicesVector;
	if (hasAnimations) {
		m_finalData->animations = animations;
	}
}


BinaryModelLoader::~BinaryModelLoader()
{
}
