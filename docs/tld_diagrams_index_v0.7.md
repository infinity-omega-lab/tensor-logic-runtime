# Tensor Logic Runtime v0.7 — Diagram Index (Codex-Oriented)

This index groups all v0.7 runtime diagrams by **canonical category**, and
provides short summaries for Codex to infer structure, roles, and compilation
order.  
All paths are relative to `A_oss_public/docs/Diagram/Codex/`.

---

## OVW — Overview

Summary:
- High-level runtime structure for v0.7.
- Shows major subsystems (CCM, DRA-v2, TIL-v2, SMM-v2, PCL-v2, AOL-v2, GDA-v2, Proto-UCG, CIM-v1).
- Serves as the **entry point** for any initial compiler or analysis pipeline.

Diagrams:
- **Runtime Overview v0.7**  
  `Diagram/Codex/tl_runtime_v0_7_overview.md`

---

## PCL / GCL / CCM — Predictive & Canonical Convergence System

Summary:
- Formalizes prediction and convergence as **canonical constraints**, not heuristics.
- Couples predictive deltas, drift envelopes, temporal windows, and structural fixes.
- GCL-v2 and CCM-v2 encode global convergence laws and cross-axis canonicalization.
- Core source for any **predictive planning / hazard handling / convergence engine** in the compiler.

Diagrams:
- **PCL v1 Internal (Predictive Convergence Layer base)**  
  `Diagram/Codex/tl_runtime_v0_7_pcl_internal.md`
- **PCL v2 Internal (Predictive Canonicalization Layer v2)**  
  `Diagram/Codex/tl_runtime_v0_7_pcl_v2_internal.md`
- **PCL v2 — B1 Layer Diagram**  
  `Diagram/Codex/tl_runtime_v0_7_B1_PCL_v2_internal.md`
- **PCC2 — Predictive Coherence Contract**  
  `Diagram/Codex/tl_runtime_v0_7_pcc2_internal.md`
- **Predictive Contraction Flow (PCF)**  
  `Diagram/Codex/tl_runtime_v0_7_predictive_contraction_flow.md`
- **GCL v2 — Global Convergence Layer (B7)**  
  `Diagram/Codex/tl_runtime_v0_7_B7_GCL_v2_internal.md`
- **CCM v2 — Canonical Convergence Model (B8)**  
  `Diagram/Codex/tl_runtime_v0_7_B8_CCM_v2_internal.md`

---

## TIL — Temporal Inference & Canonical Time

Summary:
- Defines temporal inference, canonical time windows, and temporal signatures.
- Governs replay ordering, phase-locking, and cross-host temporal consistency.
- Any compiler pass dealing with **timeline, replay, or scheduling** should align to these diagrams.

Diagrams:
- **TIL v1 Internal (Temporal Inference Layer base)**  
  `Diagram/Codex/tl_runtime_v0_7_til_internal.md`
- **TIL v2 Internal (Temporal Inference Layer v2)**  
  `Diagram/Codex/tl_runtime_v0_7_til_v2_internal.md`
- **TSIG v2 — Temporal Signature Model**  
  `Diagram/Codex/tl_runtime_v0_7_tsig_v2_internal.md`

---

## GDA / GDL — Global Diagnostic & Drift Lineage

Summary:
- GDA/GDL define diagnostic streams, drift tracking, and canonical verification.
- Integrates structural, semantic, temporal, and predictive diagnostics.
- Basis for **debugging, audit, and canonical replay verification** in compilers.

Diagrams:
- **GDA v1 Internal — Global Diagnostic Architecture base**  
  `Diagram/Codex/tl_runtime_v0_7_gda_internal.md`
- **GDA v2 Internal — GDA-v2 core**  
  `Diagram/Codex/tl_runtime_v0_7_gda_v2_internal.md`
- **GDL v2 — Global Drift Lineage / Diagnostic Lineage**  
  `Diagram/Codex/tl_runtime_v0_7_gdl_v2_internal.md`
- **GDA v2 — B4 Layer Diagram**  
  `Diagram/Codex/tl_runtime_v0_7_B4_GDA_v2_internal.md`

---

## SMM — Semantic Meaning Model

Summary:
- Encodes the semantic manifold model and canonical meaning anchors.
- Defines drift envelopes in semantic space and their coupling to prediction and structure.
- Compiler semantic passes (type-like reasoning, semantic consistency checks) rely on this layer.

Diagrams:
- **SMM v1 Internal — Semantic Meaning Model base**  
  `Diagram/Codex/tl_runtime_v0_7_smm_internal.md`
- **SMM v2 — B3 Layer Diagram**  
  `Diagram/Codex/tl_runtime_v0_7_B3_SMM_v2_internal.md`

---

## AOL — Adaptive Optimization Layer

Summary:
- Treats optimization as **canonical control**, not ad-hoc heuristics.
- Connects fusion graphs, cost models, and stability envelopes (SSB/PSB/CSB/TDB/DSB).
- Any compiler optimization (fusion, scheduling, placement) must comply with AOL invariants.

Diagrams:
- **AOL v1 Internal — Adaptive Optimization Layer base**  
  `Diagram/Codex/tl_runtime_v0_7_aol_internal.md`
- **AOL v2 — B5 Layer Diagram**  
  `Diagram/Codex/tl_runtime_v0_7_B5_AOL_v2_internal.md`

---

## DRA / DPC / DTC — Distributed Runtime Architecture v2

Summary:
- Defines host graph, Host Evaluation Regions (HERs), and distributed execution episodes (DEEs).
- DPC/DTC describe distributed pipelines and transition logic between regions/hosts.
- This is the entry point for any compiler targeting **multi-host execution**.

Diagrams:
- **DRA v1 Internal — Distributed Runtime Architecture base**  
  `Diagram/Codex/tl_runtime_v0_7_dra_internal.md`
- **DRA v2 — B6 Layer Diagram**  
  `Diagram/Codex/tl_runtime_v0_7_B6_DRA_v2_internal.md`
- **DPC v2 — Distributed Pipeline Control**  
  `Diagram/Codex/tl_runtime_v0_7_dpc_v2_internal.md`
- **DTC v2 — Distributed Transition Control**  
  `Diagram/Codex/tl_runtime_v0_7_dtc_v2_internal.md`

---

## MIG / XHM — Cross-Host Execution & Migration

Summary:
- Describes cross-host migration of execution state under DRA-v2 and CCMv2 rules.
- Ensures migration preserves canonical identity, convergence contracts, and replayability.
- Compilers using live migration or elasticity mechanisms should consult this.

Diagrams:
- **Cross-Host Migration Pipeline v2**  
  `Diagram/Codex/tl_runtime_v0_7_cross_host_migration_pipeline_internal.md`

---

## UCG / CIM / CHIP / UCR — Canonical Graph & Identity Core

Summary:
- Proto-UCG, node structure, and canonical identity model (CIM v1) live here.
- CHIP v2 defines canonical host/identity projection; UCR diagrams show the UCR boundary.
- This cluster defines how **all runtime states** embed into a unified canonical graph and identity space.

Diagrams:
- **Proto-UCG Integration — Mapping runtime to UCG**  
  `Diagram/Codex/tl_runtime_v0_7_proto_to_ucg_internal.md`
- **UCG Node Structure**  
  `Diagram/Codex/tl_runtime_v0_7_ucg_node_structure_internal.md`
- **CHIP v2 — Canonical Host / Identity Projection**  
  `Diagram/Codex/tl_runtime_v0_7_chip_v2_internal.md`
- **CIM v1 — Canonical Identity Model base**  
  `Diagram/Codex/tl_runtime_v0_7_cim_v1_internal.md`
- **CIM v1 Persistence Model**  
  `Diagram/Codex/tl_runtime_v0_7_cim_v1_persistence_internal.md`
- **CIM v1 → v2 Transition**  
  `Diagram/Codex/tl_runtime_v0_7_cim_v1_to_v2_transition_internal.md`
- **UCR Integration — Unified Canonical Runtime boundary**  
  `Diagram/Codex/tl_runtime_v0_7_ucr_internal.md`

---

## RDE / CRP — Replay & Deterministic Regeneration

Summary:
- RDE v2 and the canonical replay pipeline define deterministic replay and regeneration.
- Ensures any distributed execution can be re-materialized as canonical single-host runs.
- Critical for **debugging, forensics, and strong determinism contracts**.

Diagrams:
- **RDE v2 — Regeneration / Replay Engine**  
  `Diagram/Codex/tl_runtime_v0_7_rde_v2_internal.md`
- **Canonical Replay Pipeline**  
  `Diagram/Codex/tl_runtime_v0_7_canonical_replay_pipeline_internal.md`

---

## Appendix / Transitional & Composite Artifacts

Summary:
- Diagrams that are composite, transitional, or do not fit solely in one category.
- May be used for cross-layer reasoning or documentation, but are not primary compiler entry points.

Diagrams:
- *(none explicitly assigned yet; this section is reserved for future additions)*

---

## Notes for Codex (Initial Compiler Generation)

1. **Start with OVW**, then traverse categories in the order of this file:
   - PCL/GCL/CCM → TIL → GDA/GDL → SMM → AOL → DRA/DPC/DTC → MIG/XHM → UCG/CIM/CHIP/UCR → RDE/CRP.
2. Treat each category as a **logical module family** when designing compiler passes.
3. Use filenames and paths as stable references; higher-level IDs (DIA-xxxx) will be provided in a separate registry JSON.
4. All diagrams under `Diagram/Codex/` are canonical for v0.7; future versions will provide parallel indices.

