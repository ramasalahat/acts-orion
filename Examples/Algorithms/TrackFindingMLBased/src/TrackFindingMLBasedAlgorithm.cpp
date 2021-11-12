// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ActsExamples/TrackFindingMLBased/TrackFindingMLBasedAlgorithm.hpp"

#include "ActsExamples/EventData/SimSpacePoint.hpp"
#include "ActsExamples/EventData/ProtoTrack.hpp"
#include "ActsExamples/EventData/Index.hpp"
#include "ActsExamples/Framework/WhiteBoard.hpp"

ActsExamples::TrackFindingMLBasedAlgorithm::TrackFindingMLBasedAlgorithm(
    Config config, Acts::Logging::Level level)
    : ActsExamples::BareAlgorithm("TrackFindingMLBasedAlgorithm", level),
      m_cfg(std::move(config)) {
  if (m_cfg.inputSpacePoints.empty()) {
    throw std::invalid_argument("Missing spacepoint input collection");
  }
  if (m_cfg.outputProtoTracks.empty()) {
    throw std::invalid_argument("Missing protoTrack output collection");
  }
}

ActsExamples::ProcessCode ActsExamples::TrackFindingMLBasedAlgorithm::execute(
  const ActsExamples::AlgorithmContext& ctx) const 
{
  if (m_cfg.trackFinder == nullptr) return ActsExamples::ProcessCode::SUCCESS;

  // Read input data
  const auto& spacepoints =
    ctx.eventStore.get<SimSpacePointContainer>(m_cfg.inputSpacePoints);

  // Convert Input data to a list of size [num_measurements x measurement_features]
  size_t num_spacepoints = spacepoints.size();
  ACTS_INFO("Received " << num_spacepoints << " spacepoints");

  std::vector<float> inputValues;
  std::vector<uint32_t> spacepointIDs;
  for(const auto& sp: spacepoints) {
    float x = sp.x();
    float y = sp.y();
    float z = sp.z();
    float r = sp.r();
    float phi = std::atan2(y, x);
    inputValues.push_back(r);
    inputValues.push_back(phi);
    inputValues.push_back(z);

    spacepointIDs.push_back(sp.measurementIndex());
  }

  // ProtoTrackContainer protoTracks;
  std::vector<std::vector<uint32_t> > protoTracks;
  m_cfg.trackFinder(inputValues, spacepointIDs, protoTracks);

  ACTS_INFO("Created " << protoTracks.size() << " proto tracks");
  ctx.eventStore.add(m_cfg.outputProtoTracks, std::move(protoTracks));

  return ActsExamples::ProcessCode::SUCCESS;
}