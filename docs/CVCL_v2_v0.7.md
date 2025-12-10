# 10. Cross-Version Compatibility Layer v2 (CVCL-v2)

## 10.1 Overview
CVCL-v2 defines the canonical compatibility, migration, and diagnostic rules governing transitions between historical internal versions of the TL Runtime (v0.4 → v0.7).  
Although earlier versions are not publicly distributed, their structural deltas and compatibility implications must be formally documented to ensure determinism and reproducibility for downstream systems.

CVCL-v2 ensures that:
- Canonical behavior remains stable across version boundaries  
- Legacy artifacts can be safely normalized and migrated  
- UCG identity continuity is preserved  
- Structural and semantic drifts are detectable and recoverable  

This chapter specifies the public OSS-facing rules without exposing internal, unpublished version documents.

---

## 10.2 Scope and Intent

### 10.2.1 Scope
CVCL-v2 defines:
- Canonical Delta Model (CDM)
- Version-bound canonicalization rules
- Forward and reverse migration pipelines
- Legacy API handling and deprecation policies
- Multi-version error models and recovery rules
- UCG projection invariants across generations

### 10.2.2 Non-scope
Not covered in this chapter:
- Internal development snapshots  
- Persona-related compatibility semantics  
- Non-deterministic migration flows  

---

## 10.3 Canonical Delta Model (CDM)

CDM describes structural, semantic, and predictive deltas between runtime versions.  
It enables deterministic detection and resolution of incompatible or ambiguous artifacts.

### 10.3.1 Structural Delta
Structural deltas include:
- Changes in canonical forms  
- Revised CCMv2 constraints  
- Modified bundle schemas  

### 10.3.2 Semantic Delta
Semantic deltas capture:
- New or deprecated semantics  
- Reinterpreted runtime invariants  
- Updated strategy for semantic drift resolution  

### 10.3.3 Predictive / Temporal Delta
Predictive deltas arise from:
- PCL-v2 contraction rule updates  
- Drift propagation model adjustments  

Temporal deltas arise from:
- TIL-v2 time-domain constraint changes  
- Snapshot boundary alignment updates  

### 10.3.4 Unsafe Deltas
A delta is unsafe when:
- It violates canonicality  
- It breaks deterministic replay  
- It produces UCG-discontinuity  
- Migration leads to unresolved drift  

Unsafe deltas require explicit mitigation rules.

---

## 10.4 Migration Pipeline v2

### 10.4.1 Canonical Pre-normalization
Before migration, all artifacts must:
- Be normalized under CCMv2  
- Have deterministic serialization  
- Include canonical hashes  

### 10.4.2 Version-Bound Canonicalization
Each version boundary enforces a canonicalization step that:
- Validates structural constraints  
- Aligns semantic attributes  
- Re-evaluates drift under PCL-v2  

### 10.4.3 Forward Migration Path (0.4 → 0.5 → 0.6 → 0.7)
Forward migration proceeds in fixed order:
1. **v0.4 → v0.5:**  
   Introduction of early diagnostic and semantic-coherence constraints  

2. **v0.5 → v0.6:**  
   Integration of UCG prototypes, predictive alignment rules  

3. **v0.6 → v0.7:**  
   Full canonicalization across structural, predictive, and temporal axes  

Artifacts must pass canonical checks at each boundary.

### 10.4.4 Reverse Compatibility Constraints
Reverse compatibility is allowed only when:
- No unsafe deltas are encountered  
- Identity continuity is maintained  
- Predictive drift remains resolvable  

Reverse migration is **never automatic** and requires explicit user affirmation.

---

## 10.5 Legacy API Handling

### 10.5.1 Deprecation Levels
Legacy APIs follow 3 deterministic levels:
1. **Deprecated:** Supported but discouraged  
2. **Legacy-Stable:** Supported under compatibility shim  
3. **Removed:** Inaccessible from v0.8+  

### 10.5.2 Compatibility Shims
A shim:
- Translates legacy semantics into v0.7 form  
- Enforces canonical constraints  
- Rejects unsafe deltas  

### 10.5.3 Removal Rules (v0.8+)
Removal is permitted when:
- Migration pathways fully cover legacy functionality  
- No public API depends on removed semantics  
- Deterministic replay remains intact  

---

## 10.6 UCG Projection Across Versions

### 10.6.1 UCG Signature Stability
UCG signatures must:
- Be preserved across all version migrations  
- Maintain canonical identity tuples  
- Avoid referential discontinuities  

### 10.6.2 Projection Rules for Mixed-version Artifacts
Mixed-version environments must:
- Normalize artifacts before projection  
- Compare drift signatures for conflicts  
- Apply resolving strategies defined in PCL-v2  

### 10.6.3 Drift Detection Between Generations
Cross-generation drift becomes detectable when:
- Semantic boundaries shift  
- Predictive state differs across versions  
- Temporal-window alignment fails  

---

## 10.7 Canonical Error Model

### 10.7.1 Version Mismatch Diagnostics
Diagnostics must detect:
- Structural mismatches  
- Semantic incompatibilities  
- UCG discontinuities  

### 10.7.2 Migration Failure Classes
Failure classes include:
- Canonical mismatch errors  
- Unsafe-delta violations  
- Projection or hashing inconsistencies  

### 10.7.3 Recovery Procedures
Recovery must:
- Re-normalize artifacts  
- Retry projection with canonical fallback  
- Provide deterministic resolution or fail safely  

---

## 10.8 Test Guidelines

### 10.8.1 Multi-version Deterministic Replay
Replay must produce identical results under:
- Equivalent host conditions  
- Mixed artifact versions  

### 10.8.2 Migration Consistency Tests
Artifacts must migrate with:
- Identical metadata  
- Identical canonical hashes  
- No drift beyond thresholds  

### 10.8.3 API-forward Compatibility Tests
APIs must operate identically when:
- Using legacy profiles  
- Using normalized v0.7 profiles  
- Running in mixed-version runtime contexts  

---

CVCL v2 must validate identity continuity with UCG v2 and diagnostic stability with GDA-v2, forming a closed compatibility loop across structural, semantic, temporal, and diagnostic dimensions.